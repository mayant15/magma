# SQLite PoCs for the hand-written harnesses

`gen_pocs.py OUTDIR` writes one input per bug (`h<harness>_<bug>.bin`).
Verified with Magma's monitor (`monitor --fetch watch --dump human
harness_N FILE`) on a canary build of the pinned snapshot:

| Bug | Harness | Triggered | How |
|-----|---------|-----------|-----|
| SQL001 | 0 | yes | FTS5 prefix query over a shorter uncommitted term |
| SQL002 | 0 | yes | view over a vtab + `trusted_schema=OFF`, or `CFG_NO_VIEW` |
| SQL003 | 0 | yes | `SELECT DISTINCT` + LEFT JOIN of a flattenable subquery |
| SQL004 | 2 | yes | `zipfile()` aggregate, directory name with embedded NUL |
| SQL005 | 2 | yes | zipfile vtab `INSERT` with NULL name |
| SQL006 | 0 | yes | DISTINCT + window + ORDER BY in a scalar subquery duplicated by an outer `ORDER BY 1` |
| SQL007 | 0, 1 | yes | `CREATE TABLE ... AS SELECT` row in `sqlite_schema` |
| SQL008 | 2 | yes | `.dump` of a schema row unknown to `PRAGMA table_info` |
| SQL009 | 0 | yes | text conversion of a zeroblob above the 25 MB heap limit |
| SQL010 | 0 | yes | 10-wide vector `IN` (WHERE-term array realloc) |
| SQL011 | 0, 1 | yes | RTree with an undersized root node |
| SQL012 | 0, 1 | yes | `integrity_check` on a NOT NULL generated column |
| SQL013 | 0 | yes | 3 stacked skip-scans from a hand-written `sqlite_stat1` |
| SQL014 | 0 | yes | "row value misused" inside a compound SELECT |
| SQL015 | 0 | yes | generated column at index < 64 in a 71-column table |
| SQL016 | 0 | reach only | see below |
| SQL017 | 0 | yes | `CFG_INTERNAL_FN`: `implies_nonnull_row()` over an index-on-expression rewrite |
| SQL018 | 0 | yes | any compound SELECT with ORDER BY |
| SQL019 | 0 | reach only | see below |
| SQL020 | 0 | yes | `PARTITION BY 1` in a window |

Magma records only the first canary that triggers in a run. SQL018 fires
on any compound `ORDER BY`, so it masks later bugs in the same input; 58 of
the default seeds trigger it.

**SQL019** can't trigger in this build. The canary needs
`e2 + precision + width > INT_MAX - 15`, but `build.sh` defines
`SQLITE_PRINTF_PRECISION_LIMIT=1048576`, which clamps both width and
precision for SQL `printf()` and the C API, and `e2` is at most ~308.

**SQL016** fires only if a comparison opcode's affinity conversion changes
an input register's `MEM_Dyn` bit without `flags1`/`flags3` following. In
this snapshot both stringify paths recompute the saved flags from the
register, numeric affinity never touches `MEM_Dyn`, and `pIn1==pIn3` is
already handled (`NEVER(...)`). Upstream keeps the same asserts. I found no
path that triggers it short of memory corruption from another bug.
