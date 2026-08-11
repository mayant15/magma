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

cd "$TARGET/repo"
./autogen.sh \
	--with-http=no \
	--with-python=no \
	--with-lzma=yes \
	--with-threads=no \
	--disable-shared
make -j$(nproc) clean
make -j$(nproc) all

# libtool merges libAFLDriver.a (from $LIBS) into the static archive as a
# nested archive member. --whole-archive cannot handle nested archives, so
# strip it before linking. libAFLDriver.a is still linked via $LIBS.
ar d .libs/libxml2.a libAFLDriver.a

cp xmllint "$OUT/"

for fuzzer in libxml2_xml_read_memory_fuzzer libxml2_xml_reader_for_file_fuzzer; do
  $CXX $CXXFLAGS -std=c++11 -Iinclude/ -I"$TARGET/src/" \
      "$TARGET/src/$fuzzer.cc" -o "$OUT/$fuzzer" \
      -Wl,--whole-archive .libs/libxml2.a -Wl,--no-whole-archive $LDFLAGS $LIBS -lz -llzma
done

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
    $RAW_CC -Iinclude/ -I"$TARGET/src/" -I"$SUPPORT" -c $HARNESS -o "$OUT/$NAME.o"
    $CC "$OUT/$NAME.o" "$RUNTIME" \
      -Wl,--whole-archive .libs/libxml2.a -Wl,--no-whole-archive \
      -o "$OUT/$NAME" -llzma -lz -lm \
      $LDFLAGS $LIBS
  done
fi
