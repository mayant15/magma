#!/bin/bash
set -e

##
# Pre-requirements:
# - env TARGET: path to target work dir
# - env OUT: path to directory where artifacts are stored
# - env CC, CXX, FLAGS, LIBS, etc...
# + env HARNESSES: path to directory with custom harnesses (default: unset)
##

if [ ! -d "$TARGET/repo" ]; then
    echo "fetch.sh must be executed first."
    exit 1
fi

# build the libpng library
cd "$TARGET/repo"
autoreconf -f -i
./configure --with-libpng-prefix=MAGMA_ --disable-shared
make -j$(nproc) clean
make -j$(nproc) libpng16.la

cp .libs/libpng16.a "$OUT/"

if [ ! -z "$HARNESSES" ]; then
  HARNESS_DIR="$TARGET/$HARNESSES"

  # TODO(Mayant): Do I want to keep this configurable? I need a non-AFL C compiler
  # here, OR use an instrumentation denylist.
  RAW_CC="clang"

  if [ ! -d "$HARNESS_DIR" ]; then
    echo "harness directory $HARNESS_DIR does not exist."
    exit 1
  fi

  echo "Building custom harnesses"
  for HARNESS in $HARNESS_DIR/*.c; do
    NAME=$(basename --suffix .c $HARNESS)
    $RAW_CC -I. -c $HARNESS -o "$OUT/$NAME.o"
    $CC "$OUT/$NAME.o" -o "$OUT/$NAME" $LDFLAGS .libs/libpng16.a $LIBS -lz
  done

else
  # build libpng_read_fuzzer.
  $CXX $CXXFLAGS -std=c++11 -I. \
       contrib/oss-fuzz/libpng_read_fuzzer.cc \
       -o $OUT/libpng_read_fuzzer \
       $LDFLAGS .libs/libpng16.a $LIBS -lz
fi
