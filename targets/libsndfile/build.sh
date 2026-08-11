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

cd "$TARGET/repo"
./autogen.sh
./configure --disable-shared --enable-ossfuzzers --prefix="$OUT"
make -j$(nproc) clean
make -j$(nproc) ossfuzz/sndfile_fuzzer
make install

# libtool merges libAFLDriver.a (from $LIBS) into the static archive as a
# nested archive member. --whole-archive cannot handle nested archives, so
# strip it before linking. libAFLDriver.a is still linked via $LIBS.
ar d "$OUT/lib/libsndfile.a" libAFLDriver.a

cp -v ossfuzz/sndfile_fuzzer $OUT/

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
    $RAW_CC -I"$OUT/include" -I"$SUPPORT" -c $HARNESS -o "$OUT/$NAME.o"
    $CC "$OUT/$NAME.o" "$RUNTIME" \
      -Wl,--whole-archive "$OUT/lib/libsndfile.a" -Wl,--no-whole-archive \
      -o "$OUT/$NAME" \
      -lm -lmpg123 -lopus -lmp3lame -lvorbis -lvorbisenc -logg -lFLAC -lasound \
      $LDFLAGS $LIBS
  done
fi

