#!/bin/bash
set -e

##
# Pre-requirements:
# - env TARGET: path to target work dir
# - env OUT: path to directory where artifacts are stored
# - env CC, CXX, FLAGS, LIBS, etc...
##

if [ ! -d "$TARGET/repo" ]; then
    echo "fetch.sh must be executed first."
    exit 1
fi

# build the sqlite3 library
cd "$TARGET/repo"

export WORK="$TARGET/work"
rm -rf "$WORK"
mkdir -p "$WORK"
cd "$WORK"

export CFLAGS="$CFLAGS -DSQLITE_MAX_LENGTH=128000000 \
               -DSQLITE_MAX_SQL_LENGTH=128000000 \
               -DSQLITE_MAX_MEMORY=25000000 \
               -DSQLITE_PRINTF_PRECISION_LIMIT=1048576 \
               -DSQLITE_DEBUG=1 \
               -DSQLITE_MAX_PAGE_COUNT=16384"

"$TARGET/repo"/configure --disable-shared --enable-rtree
make clean
make -j$(nproc)
make sqlite3.c

$CC $CFLAGS -I. \
    "$TARGET/repo/test/ossfuzz.c" -Wl,--whole-archive "./sqlite3.o" -Wl,--no-whole-archive \
    -o "$OUT/sqlite3_fuzz" \
    $LDFLAGS $LIBS -pthread -ldl -lm

if [ ! -z "$HARNESSES" ]; then
  HARNESS_DIR="$TARGET/$HARNESSES"
  if [ ! -d "$HARNESS_DIR" ]; then
    echo "harness directory $HARNESS_DIR does not exist."
    exit 1
  fi

  RAW_CC="clang"

  SUPPORT="$TARGET/traffic/support"
  RUNTIME="$OUT/runtime.o"
  $RAW_CC -I"$SUPPORT" -c "$SUPPORT/runtime.c" -o "$RUNTIME"

  for HARNESS in $HARNESS_DIR/*.c; do
    NAME=$(basename $HARNESS .c)
    echo "building $NAME"
    $RAW_CC -I. -I"$SUPPORT" -c $HARNESS -o "$OUT/$NAME.o"
    $CC "$OUT/$NAME.o" "$RUNTIME" \
      -Wl,--whole-archive "./sqlite3.o" -Wl,--no-whole-archive \
      -o "$OUT/$NAME" -pthread -ldl -lm \
      $LDFLAGS $LIBS
  done
fi

