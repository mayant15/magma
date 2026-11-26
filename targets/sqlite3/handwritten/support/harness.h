/* Shared plumbing for the hand-written SQLite harnesses.
 *
 * Each harness defines `static int fuzz_one(const uint8_t *, size_t)`; this
 * header supplies a file-reading main() (AFL `@@` style, like the traffic and
 * ogharn harnesses) plus:
 *
 *  - a 4-byte little-endian configuration word at the start of every input.
 *    The default corpus already starts with four NUL bytes (for the combined
 *    ogharn/traffic harnesses), so every seed runs with the default
 *    configuration and the fuzzer can flip bits to explore the others.
 *  - a connection factory that applies the configuration (db_config flags,
 *    internal SQL functions, disabled optimizations, encoding, ...) and
 *    registers FTS5 (SQL001 lives in ext/fts5, which the target's sqlite3.o
 *    does not contain; build.sh compiles the generated fts5.c amalgamation).
 *  - a VM-step budget (progress handler) so recursive CTEs etc. terminate.
 *  - a file sandbox: file names containing '/' are refused and plain names
 *    are mapped into a private, lazily created temporary directory that is
 *    removed at exit. Applies to every SQLite VFS open (ATTACH, VACUUM INTO,
 *    ...) and, in harness_2, to the CLI's stdio (zipfile archives).
 */

#ifndef SQLITE3_HANDWRITTEN_HARNESS_H
#define SQLITE3_HANDWRITTEN_HARNESS_H

#define _GNU_SOURCE
#include "sqlite3.h"

#include <dirent.h>
#include <errno.h>
#include <ftw.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ---- configuration ------------------------------------------------------ */

#define CFG_FKEY        (1u << 0)  /* SQLITE_DBCONFIG_ENABLE_FKEY */
#define CFG_INTERNAL_FN (1u << 1)  /* SQLITE_TESTCTRL_INTERNAL_FUNCTIONS */
#define CFG_DEFENSIVE   (1u << 2)  /* SQLITE_DBCONFIG_DEFENSIVE */
#define CFG_UNTRUSTED   (1u << 3)  /* SQLITE_DBCONFIG_TRUSTED_SCHEMA = 0 */
#define CFG_NO_VIEW     (1u << 4)  /* SQLITE_DBCONFIG_ENABLE_VIEW = 0 */
#define CFG_NO_TRIGGER  (1u << 5)  /* SQLITE_DBCONFIG_ENABLE_TRIGGER = 0 */
#define CFG_LEGACY_ALTER (1u << 6) /* SQLITE_DBCONFIG_LEGACY_ALTER_TABLE */
#define CFG_NO_DQS      (1u << 7)  /* double-quoted strings disabled */
#define CFG_REVERSE     (1u << 8)  /* PRAGMA reverse_unordered_selects */
#define CFG_UTF16       (1u << 9)  /* PRAGMA encoding=UTF-16le */
#define CFG_ONE_STEP    (1u << 10) /* harness-specific */
#define CFG_EXTRA       (1u << 11) /* harness-specific */
/* bits 12-15: reserved
 * bits 16-31: SQLITE_TESTCTRL_OPTIMIZATIONS mask (set bit = disable):
 *   0x0001 QueryFlattener  0x0002 WindowFunc     0x0004 GroupByOrder
 *   0x0008 FactorOutConst  0x0010 DistinctOpt    0x0020 CoverIdxScan
 *   0x0040 OrderByIdxJoin  0x0080 Transitive     0x0100 OmitNoopJoin
 *   0x0200 CountOfView     0x0400 CursorHints    0x0800 Stat4
 *   0x1000 PushDown        0x2000 SimplifyJoin   0x4000 SkipScan
 *   0x8000 PropagateConst */

typedef struct {
  uint32_t flags;    /* CFG_* bits */
  uint32_t optmask;  /* optimizations to disable */
} harness_cfg;

/* Consume the 4-byte config prefix. Inputs shorter than that run with the
 * default configuration and are used in full. */
static inline harness_cfg harness_config(const uint8_t **data, size_t *size) {
  harness_cfg cfg = {0, 0};
  uint32_t raw = 0;
  if (*size >= 4) {
    raw = (uint32_t)(*data)[0] | (uint32_t)(*data)[1] << 8 |
          (uint32_t)(*data)[2] << 16 | (uint32_t)(*data)[3] << 24;
    *data += 4;
    *size -= 4;
  }
  cfg.flags = raw & 0xffff;
  cfg.optmask = raw >> 16;
  return cfg;
}

/* ---- file sandbox --------------------------------------------------------- */

static char harness_tmpdir[64];

static int harness_rm_cb(const char *path, const struct stat *sb, int flag,
                         struct FTW *ftw) {
  (void)sb; (void)flag; (void)ftw;
  return remove(path);
}

static void harness_cleanup(void) {
  if (harness_tmpdir[0])
    nftw(harness_tmpdir, harness_rm_cb, 8, FTW_DEPTH | FTW_PHYS);
}

/* A run that crashes (i.e. found a bug) skips atexit(). Rather than cleaning
 * up from a signal handler (which could deadlock on a corrupted heap and
 * turn the crash into a hang), sweep directories left by dead processes
 * whenever a new one is created. */
static void harness_sweep_stale(const char *base) {
  DIR *dir = opendir(base);
  struct dirent *de;
  char path[512];
  if (dir == NULL)
    return;
  while ((de = readdir(dir)) != NULL) {
    long pid;
    if (strncmp(de->d_name, "sqlite-hw-", 10) != 0)
      continue;
    pid = strtol(de->d_name + 10, NULL, 10);
    if (pid <= 0 || kill((pid_t)pid, 0) == 0 || errno != ESRCH)
      continue;
    if ((size_t)snprintf(path, sizeof path, "%s/%s", base, de->d_name) <
        sizeof path)
      nftw(path, harness_rm_cb, 8, FTW_DEPTH | FTW_PHYS);
  }
  closedir(dir);
}

/* Map a file name into the sandbox directory. Returns 0 and fills `out` on
 * success, -1 if the name is not allowed. */
static int harness_sandbox_path(const char *name, char *out, size_t nout) {
  if (name == NULL || name[0] == 0 || strchr(name, '/') != NULL ||
      strcmp(name, ".") == 0 || strcmp(name, "..") == 0)
    return -1;
  if (harness_tmpdir[0] == 0) {
    const char *base = getenv("TMPDIR");
    if (base == NULL || base[0] == 0 || strlen(base) >= 32)
      base = "/tmp";
    harness_sweep_stale(base);
    snprintf(harness_tmpdir, sizeof harness_tmpdir, "%s/sqlite-hw-%ld-XXXXXX",
             base, (long)getpid());
    if (mkdtemp(harness_tmpdir) == NULL) {
      harness_tmpdir[0] = 0;
      return -1;
    }
    atexit(harness_cleanup);
  }
  if ((size_t)snprintf(out, nout, "%s/%s", harness_tmpdir, name) >= nout)
    return -1;
  return 0;
}

/* stdio replacement for code compiled into the harness (the CLI). */
static FILE *harness_fopen(const char *name, const char *mode) {
  char path[512];
  if (harness_sandbox_path(name, path, sizeof path))
    return NULL;
  return fopen(path, mode);
}

/* A VFS that delegates to the default one but only resolves sandboxed names.
 * SQLite runs every database / journal name through xFullPathname before
 * xOpen, so filtering there covers ATTACH, VACUUM INTO, URI names, ... */
static sqlite3_vfs harness_vfs;
static sqlite3_vfs *harness_base_vfs;

static int harness_full_pathname(sqlite3_vfs *vfs, const char *name, int n,
                                 char *out) {
  char path[512];
  (void)vfs;
  if (harness_sandbox_path(name, path, sizeof path))
    return SQLITE_CANTOPEN;
  return harness_base_vfs->xFullPathname(harness_base_vfs, path, n, out);
}

static void harness_register_vfs(void) {
  if (harness_base_vfs != NULL)
    return;
  harness_base_vfs = sqlite3_vfs_find(0);
  if (harness_base_vfs == NULL)
    return;
  harness_vfs = *harness_base_vfs;
  harness_vfs.zName = "harness";
  harness_vfs.xFullPathname = harness_full_pathname;
  /* Extension hooks for loadable modules: never needed, never allowed. */
  harness_vfs.xDlOpen = NULL;
  sqlite3_vfs_register(&harness_vfs, 1);
}

/* ---- connection ------------------------------------------------------------- */

int sqlite3Fts5Init(sqlite3 *db); /* from fts5.c, built by build.sh */

#define HARNESS_PROGRESS_OPS 1000
#define HARNESS_MAX_PROGRESS 20000 /* ~20M VM steps per input */

static unsigned harness_progress_calls;

static int harness_progress(void *arg) {
  (void)arg;
  return ++harness_progress_calls > HARNESS_MAX_PROGRESS;
}

/* Deny pragmas that only produce huge debug traces (SQLITE_DEBUG build) or
 * redirect temporary files outside the sandbox. */
static int harness_authorizer(void *arg, int op, const char *a, const char *b,
                              const char *c, const char *d) {
  (void)arg; (void)b; (void)c; (void)d;
  if (op == SQLITE_PRAGMA && a != NULL) {
    if (sqlite3_strnicmp(a, "vdbe_", 5) == 0 ||
        sqlite3_stricmp(a, "parser_trace") == 0 ||
        sqlite3_stricmp(a, "temp_store_directory") == 0 ||
        sqlite3_stricmp(a, "data_store_directory") == 0)
      return SQLITE_DENY;
  }
  return SQLITE_OK;
}

static void harness_db_config(sqlite3 *db, int op, int on) {
  int ignored;
  sqlite3_db_config(db, op, on, &ignored);
}

static sqlite3 *harness_open(const harness_cfg *cfg) {
  sqlite3 *db = NULL;
  uint32_t f = cfg->flags;

  harness_register_vfs();
  if (sqlite3_open_v2(":memory:", &db,
                      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) {
    sqlite3_close(db);
    return NULL;
  }
  harness_progress_calls = 0;
  sqlite3_progress_handler(db, HARNESS_PROGRESS_OPS, harness_progress, NULL);
  sqlite3_limit(db, SQLITE_LIMIT_VDBE_OP, 25000);
  sqlite3_set_authorizer(db, harness_authorizer, NULL);
  sqlite3Fts5Init(db);

  harness_db_config(db, SQLITE_DBCONFIG_ENABLE_FKEY, (f & CFG_FKEY) != 0);
  harness_db_config(db, SQLITE_DBCONFIG_DEFENSIVE, (f & CFG_DEFENSIVE) != 0);
  harness_db_config(db, SQLITE_DBCONFIG_TRUSTED_SCHEMA, !(f & CFG_UNTRUSTED));
  harness_db_config(db, SQLITE_DBCONFIG_ENABLE_VIEW, !(f & CFG_NO_VIEW));
  harness_db_config(db, SQLITE_DBCONFIG_ENABLE_TRIGGER, !(f & CFG_NO_TRIGGER));
  harness_db_config(db, SQLITE_DBCONFIG_LEGACY_ALTER_TABLE,
                    (f & CFG_LEGACY_ALTER) != 0);
  harness_db_config(db, SQLITE_DBCONFIG_DQS_DML, !(f & CFG_NO_DQS));
  harness_db_config(db, SQLITE_DBCONFIG_DQS_DDL, !(f & CFG_NO_DQS));
  if (f & CFG_INTERNAL_FN)
    sqlite3_test_control(SQLITE_TESTCTRL_INTERNAL_FUNCTIONS, db);
  if (cfg->optmask)
    sqlite3_test_control(SQLITE_TESTCTRL_OPTIMIZATIONS, db, cfg->optmask);
  if (f & CFG_REVERSE)
    sqlite3_exec(db, "PRAGMA reverse_unordered_selects=1", 0, 0, 0);
  if (f & CFG_UTF16)
    sqlite3_exec(db, "PRAGMA encoding='UTF-16le'", 0, 0, 0);
  return db;
}

/* NUL-terminated copy of the SQL text (sqlite3_prepare/exec need one). */
static char *harness_strndup(const uint8_t *data, size_t size) {
  char *z = (char *)malloc(size + 1);
  if (z != NULL) {
    memcpy(z, data, size);
    z[size] = 0;
  }
  return z;
}

/* Run every statement of `sql`, stepping each to completion (or the
 * progress budget). Errors only end the current statement, so later
 * statements still run; a statement that fails to prepare is skipped up to
 * the parser's tail. */
static void harness_run_sql(sqlite3 *db, const char *sql) {
  const char *z = sql;
  while (z != NULL && *z) {
    sqlite3_stmt *stmt = NULL;
    const char *tail = NULL;
    int rc = sqlite3_prepare_v2(db, z, -1, &stmt, &tail);
    if (rc != SQLITE_OK || stmt == NULL) {
      if (tail == NULL || tail == z)
        break;
      z = tail;
      continue;
    }
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      int i, n = sqlite3_column_count(stmt);
      /* Materialize results the way applications do (text conversion). */
      for (i = 0; i < n; i++)
        sqlite3_column_text(stmt, i);
    }
    sqlite3_finalize(stmt);
    if (harness_progress_calls > HARNESS_MAX_PROGRESS)
      break;
    z = tail;
  }
}

/* ---- main ------------------------------------------------------------------- */

static int fuzz_one(const uint8_t *data, size_t size);

int main(int argc, char *argv[]) {
  FILE *f;
  long size;
  uint8_t *buf;
  int ret;

  if (argc < 2)
    return 0;

  f = fopen(argv[1], "rb");
  if (f == NULL)
    return 0;

  fseek(f, 0, SEEK_END);
  size = ftell(f);
  rewind(f);
  if (size < 1) {
    fclose(f);
    return 0;
  }

  buf = (uint8_t *)malloc((size_t)size);
  if (buf == NULL || fread(buf, (size_t)size, 1, f) != 1) {
    fclose(f);
    free(buf);
    return 0;
  }
  fclose(f);

  ret = fuzz_one(buf, (size_t)size);
  free(buf);
  return ret;
}

#endif /* SQLITE3_HANDWRITTEN_HARNESS_H */
