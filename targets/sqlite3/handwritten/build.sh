#!/bin/bash
##
# Harness build for targets/sqlite3/handwritten, sourced by the target's
# build.sh after the library is built (CWD = $WORK, which holds sqlite3.o,
# sqlite3.h and the generated shell.c / fts5.c).
#
# Unlike the default recipe, the harnesses are compiled with $CC $CFLAGS:
# fts5.c and shell.c contain bug sites (SQL001, SQL004, SQL005, SQL008), so
# they need the fuzzer's instrumentation and Magma's canaries.
##
set -e

cd "$WORK"
make fts5.c

SUPPORT="$HARNESS_DIR/support"

# FTS5 is not part of the target's sqlite3.o; build it in as a core module
# (sqlite3Fts5Init is called by support/harness.h).
$CC $CFLAGS -I. -DSQLITE_CORE -DSQLITE_ENABLE_FTS5 -c fts5.c -o "$OUT/fts5.o"

for HARNESS in "$HARNESS_DIR"/*.c; do
  NAME=$(basename "$HARNESS" .c)
  echo "building $NAME"
  EXTRA=""
  if [ "$NAME" = "harness_2" ]; then
    # The CLI: keep zipfile/sqlar, drop .system/.shell/edit().
    EXTRA="-DSQLITE_HAVE_ZLIB=1 -DSQLITE_NOHAVE_SYSTEM -DSQLITE_OMIT_LOAD_EXTENSION"
  fi
  $CC $CFLAGS $EXTRA -I. -I"$SUPPORT" -c "$HARNESS" -o "$OUT/$NAME.o"
  $CC "$OUT/$NAME.o" "$OUT/fts5.o" \
    -Wl,--whole-archive ./sqlite3.o -Wl,--no-whole-archive \
    -o "$OUT/$NAME" -lz -pthread -ldl -lm \
    $LDFLAGS $LIBS
done
