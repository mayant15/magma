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

WORK="$TARGET/work"
rm -rf "$WORK"
mkdir -p "$WORK"
mkdir -p "$WORK/lib" "$WORK/include"

cd "$TARGET/repo"
autoreconf --install --force
./configure --disable-shared --prefix="$WORK"
make -j$(nproc) clean
make -j$(nproc)
make install

# libtool merges libAFLDriver.a (from $LIBS) into the static archives as a
# nested archive member. --whole-archive cannot handle nested archives, so
# strip it before linking. libAFLDriver.a is still linked via $LIBS.
ar d "$WORK/lib/libtiff.a" libAFLDriver.a
ar d "$WORK/lib/libtiffxx.a" libAFLDriver.a

cp "$WORK/bin/tiffcp" "$OUT/"
$CXX $CXXFLAGS -std=c++11 -I$WORK/include \
    contrib/oss-fuzz/tiff_read_rgba_fuzzer.cc -o $OUT/tiff_read_rgba_fuzzer \
    -Wl,--whole-archive $WORK/lib/libtiffxx.a $WORK/lib/libtiff.a -Wl,--no-whole-archive \
    -lz -ljpeg -Wl,-Bstatic -llzma -Wl,-Bdynamic \
    $LDFLAGS $LIBS

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
    $RAW_CC -I"$WORK/include" -I"$SUPPORT" -c $HARNESS -o "$OUT/$NAME.o"
    $CC "$OUT/$NAME.o" "$RUNTIME" \
      -Wl,--whole-archive \
        "$WORK/lib/libtiffxx.a" "$WORK/lib/libtiff.a" \
      -Wl,--no-whole-archive \
      -lz -llzma -ljpeg -lm \
      -o "$OUT/$NAME" $LDFLAGS $LIBS
  done
fi
