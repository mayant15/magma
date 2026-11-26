/* sqlite3 command-line shell: run a CLI script (SQL plus dot-commands)
 * through the shell's own input loop.
 *
 * The shell (shell.c, generated from src/shell.c.in at build time) is
 * compiled into this translation unit, which brings in the extensions it
 * bundles -- zipfile, sqlar, shathree, series, ... -- and its dot-commands.
 * SQL004, SQL005 (ext/misc/zipfile.c) and SQL008 (shell.c.in) exist only
 * there.
 *
 * Input: 4-byte config word (see support/harness.h), then a CLI script.
 *   CFG_ONE_STEP  .bail on
 *   CFG_EXTRA     start in ".mode insert" (exercises the quoting paths)
 *
 * Safety: the shell is built with SQLITE_NOHAVE_SYSTEM (no .system/.shell/
 * edit()), its stdio goes through the harness file sandbox, the fileio
 * extension (writefile/lsdir) is not registered, and only an allow-list of
 * dot-commands is passed through: anything that loads libraries, runs
 * programs, sleeps, or reads/writes arbitrary paths is dropped.
 *
 *   SQL004  zipfile() aggregate (or zipfile vtab INSERT) of a directory whose
 *           name has an embedded NUL and no trailing '/'
 *   SQL005  INSERT into a zipfile vtab with a NULL name
 *   SQL008  .dump of a sqlite_schema "table" row that PRAGMA table_info
 *           does not know (planted with writable_schema)
 */

#include "harness.h"

#include <ctype.h>

/* ---- the shell ------------------------------------------------------------ */

static FILE *harness_real_fopen(const char *name, const char *mode) {
  return fopen(name, mode);
}

#define fopen harness_fopen
#define main sqlite3_shell_main
#include "shell.c"
#undef main
#undef fopen

/* ---- dot-command allow-list ---------------------------------------------- */

static const char *const allowed_dot_commands[] = {
    "binary",  "bail",     "changes",  "databases", "dbconfig", "dbinfo",
    "dump",    "echo",     "eqp",      "explain",   "expert",   "fullschema",
    "headers", "imposter", "indexes",  "indices",   "limit",    "lint",
    "mode",    "nullvalue", "parameter", "print",   "prompt",   "quit",
    "scanstats", "schema", "selftest", "separator", "sha3sum",  "show",
    "stats",   "tables",   "unmodule", "vfsinfo",   "vfslist",  "vfsname",
    "width",
};

/* Dot-commands match exactly (the shell itself also accepts prefixes; an
 * exact name can only ever select the intended command). */
static int dot_command_allowed(const char *line, size_t len) {
  size_t i = 0, n;
  while (i < len && isspace((unsigned char)line[i]))
    i++;
  if (i >= len || line[i] != '.')
    return 1; /* not a dot-command */
  i++;
  for (n = 0; i + n < len && !isspace((unsigned char)line[i + n]); n++)
    ;
  for (size_t k = 0; k < sizeof allowed_dot_commands / sizeof *allowed_dot_commands; k++)
    if (strlen(allowed_dot_commands[k]) == n &&
        memcmp(allowed_dot_commands[k], line + i, n) == 0)
      return 1;
  return 0;
}

/* Copy the script, blanking lines that start a disallowed dot-command. Line
 * structure is kept so line numbers in shell messages still match. */
static char *filter_script(const uint8_t *data, size_t size, size_t *out_len) {
  char *out = (char *)malloc(size + 1);
  size_t i = 0, o = 0;
  if (out == NULL)
    return NULL;
  while (i < size) {
    size_t end = i;
    while (end < size && data[end] != '\n')
      end++;
    if (dot_command_allowed((const char *)data + i, end - i)) {
      memcpy(out + o, data + i, end - i);
      o += end - i;
    }
    if (end < size)
      out[o++] = '\n';
    i = end + 1;
  }
  out[o] = 0;
  *out_len = o;
  return out;
}

/* Everything open_db() registers except fileio (writefile, lsdir, ...),
 * usleep and edit. */
static void register_shell_functions(ShellState *p) {
  sqlite3 *db = p->db;
  sqlite3_shathree_init(db, 0, 0);
  sqlite3_completion_init(db, 0, 0);
  sqlite3_uint_init(db, 0, 0);
  sqlite3_decimal_init(db, 0, 0);
  sqlite3_regexp_init(db, 0, 0);
  sqlite3_ieee_init(db, 0, 0);
  sqlite3_series_init(db, 0, 0);
  sqlite3_zipfile_init(db, 0, 0);
  sqlite3_sqlar_init(db, 0, 0);
  sqlite3_create_function(db, "shell_add_schema", 3, SQLITE_UTF8, 0,
                          shellAddSchemaName, 0, 0);
  sqlite3_create_function(db, "shell_module_schema", 1, SQLITE_UTF8, 0,
                          shellModuleSchema, 0, 0);
  sqlite3_create_function(db, "shell_putsnl", 1, SQLITE_UTF8, p,
                          shellPutsFunc, 0, 0);
  sqlite3_create_function(db, "shell_escape_crnl", 1, SQLITE_UTF8, 0,
                          shellEscapeCrnl, 0, 0);
  sqlite3_create_function(db, "shell_int32", 2, SQLITE_UTF8, 0, shellInt32,
                          0, 0);
  sqlite3_create_function(db, "shell_idquote", 1, SQLITE_UTF8, 0,
                          shellIdQuote, 0, 0);
}

static ShellState shell;

static int fuzz_one(const uint8_t *data, size_t size) {
  harness_cfg cfg = harness_config(&data, &size);
  char *script;
  size_t len;
  FILE *in, *devnull;

  if (size == 0)
    return 0;

  /* main_init() calls sqlite3_config(), so it must precede harness_open(). */
  main_init(&shell);
  stdin_is_interactive = 0;
  stdout_is_console = 0;
  bail_on_error = (cfg.flags & CFG_ONE_STEP) != 0;

  devnull = harness_real_fopen("/dev/null", "w");
  if (devnull == NULL)
    return 0;
  shell.out = devnull;

  shell.db = harness_open(&cfg);
  if (shell.db == NULL)
    return 0;
  globalDb = shell.db;
  shell.zDbFilename = ":memory:";
  shell.openMode = SHELL_OPEN_NORMAL;
  register_shell_functions(&shell);
  if (cfg.flags & CFG_EXTRA) {
    shell.mode = MODE_Insert;
    set_table_name(&shell, "t");
  }

  script = filter_script(data, size, &len);
  if (script != NULL) {
    in = fmemopen(script, len ? len : 1, "r");
    if (in != NULL) {
      shell.in = in;
      process_input(&shell);
      fclose(in);
    }
    free(script);
  }

  /* Mirror the shell's own teardown. */
  set_table_name(&shell, 0);
  if (shell.db)
    sqlite3_close(shell.db);
  globalDb = 0;
  fclose(devnull);
  return 0;
}
