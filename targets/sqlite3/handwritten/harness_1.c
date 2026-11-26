/* Database image + SQL (in the style of SQLite's dbsqlfuzz): deserialize an
 * attacker-controlled database file into "main", then run SQL against it.
 *
 * Input: 4-byte config word (see support/harness.h), then
 *          u32le N | N bytes of database image | SQL text
 *        If N is 0 or larger than what follows, there is no image and
 *        everything after the config word is SQL (so plain SQL seeds work).
 *   CFG_ONE_STEP  deserialize read-only
 *   CFG_EXTRA     run PRAGMA integrity_check before the SQL
 *
 * The schema of the image is parsed on first use, which is how corrupt or
 * hand-crafted schemas reach the parser and virtual-table constructors:
 *   SQL007  sqlite_schema row "CREATE TABLE t AS SELECT ..."
 *   SQL011  RTree whose %_node root blob is undersized
 *   SQL012  NOT NULL generated column + integrity_check
 * plus all the SQL-level bugs of harness_0.
 */

#include "harness.h"

static int fuzz_one(const uint8_t *data, size_t size) {
  harness_cfg cfg = harness_config(&data, &size);
  sqlite3 *db;
  char *sql;
  size_t ndb = 0;

  if (size >= 4) {
    ndb = (size_t)data[0] | (size_t)data[1] << 8 | (size_t)data[2] << 16 |
          (size_t)data[3] << 24;
    if (ndb == 0 || ndb > size - 4) {
      ndb = 0;
    } else {
      data += 4;
      size -= 4;
    }
  }

  db = harness_open(&cfg);
  if (db == NULL)
    return 0;

  if (ndb > 0) {
    unsigned char *img = (unsigned char *)sqlite3_malloc64(ndb);
    unsigned flags = SQLITE_DESERIALIZE_FREEONCLOSE;
    if (img == NULL)
      goto out;
    memcpy(img, data, ndb);
    flags |= (cfg.flags & CFG_ONE_STEP) ? SQLITE_DESERIALIZE_READONLY
                                        : SQLITE_DESERIALIZE_RESIZEABLE;
    /* On failure the image is freed by sqlite3_deserialize itself. */
    sqlite3_deserialize(db, "main", img, (sqlite3_int64)ndb,
                        (sqlite3_int64)ndb, flags);
    data += ndb;
    size -= ndb;
  }

  if (cfg.flags & CFG_EXTRA)
    harness_run_sql(db, "PRAGMA integrity_check;");

  sql = harness_strndup(data, size);
  if (sql != NULL) {
    harness_progress_calls = 0;
    harness_run_sql(db, sql);
    free(sql);
  }
out:
  sqlite3_close(db);
  return 0;
}
