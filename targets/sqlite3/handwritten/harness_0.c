/* SQL engine: run a script of SQL statements on an in-memory database.
 *
 * Input: 4-byte config word (see support/harness.h), then SQL text.
 *   CFG_ONE_STEP  run through sqlite3_exec() instead of prepare/step
 *   CFG_EXTRA     finish with PRAGMA integrity_check / quick_check
 *
 * Everything below is plain SQL on the default config unless noted:
 *   SQL001  FTS5 prefix query over uncommitted (in-memory hash) terms shorter
 *           than the prefix
 *   SQL002  error inside selectExpander's FROM loop that does not abort, e.g.
 *           a view over a virtual table with PRAGMA trusted_schema=OFF
 *           ("unsafe use of virtual table") or CFG_NO_VIEW
 *   SQL003  SELECT DISTINCT over a LEFT JOIN with a flattenable subquery
 *   SQL006  DISTINCT + window function + ORDER BY in a scalar subquery that
 *           an outer ORDER BY alias duplicates
 *   SQL007  CREATE TABLE ... AS SELECT planted in sqlite_schema
 *           (writable_schema) and loaded by a schema reparse
 *   SQL009  text conversion of a zeroblob too large for the heap limit
 *   SQL010  vector IN (a,b,...) wider than the static WHERE-term array
 *   SQL011  RTree whose node blob was shrunk, reconnected after a reparse
 *   SQL012  PRAGMA integrity_check on a NOT NULL generated column
 *   SQL013  >= 3 stacked skip-scans (hand-written sqlite_stat1)
 *   SQL014  codegen error ("row value misused") inside a compound SELECT
 *   SQL015  generated column below index 64 in a table with >= 64 columns
 *   SQL017  CFG_INTERNAL_FN: implies_nonnull_row() over an expression that
 *           an index-on-expression rewrote into an index column
 *   SQL018  compound SELECT with ORDER BY (collation added without dequote)
 *   SQL020  window ORDER BY / PARTITION BY on an integer constant
 * SQL016 and SQL019 are reached but, as far as I can tell, not triggerable
 * in this build (see pocs/README.md).
 */

#include "harness.h"

static int exec_cb(void *arg, int n, char **vals, char **cols) {
  (void)arg; (void)n; (void)vals; (void)cols;
  return harness_progress_calls > HARNESS_MAX_PROGRESS;
}

static int fuzz_one(const uint8_t *data, size_t size) {
  harness_cfg cfg = harness_config(&data, &size);
  sqlite3 *db;
  char *sql;

  if (size == 0)
    return 0;
  db = harness_open(&cfg);
  if (db == NULL)
    return 0;
  sql = harness_strndup(data, size);
  if (sql != NULL) {
    if (cfg.flags & CFG_ONE_STEP)
      sqlite3_exec(db, sql, exec_cb, NULL, NULL);
    else
      harness_run_sql(db, sql);
    if (cfg.flags & CFG_EXTRA) {
      harness_progress_calls = 0;
      harness_run_sql(db, "PRAGMA integrity_check; PRAGMA quick_check;");
    }
    free(sql);
  }
  sqlite3_close(db);
  return 0;
}
