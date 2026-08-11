##
# Build script for Traffic generated callback harnesses.
#
# These harnesses define LLVMFuzzerTestOneInput and use the Traffic runtime
# (FuzzedDataProvider) and xml2-support wrappers from traffic/support/.
#
# Sourced by targets/libxml2/build.sh — inherits its environment:
# - CWD is $TARGET/repo (where .libs/libxml2.a and include/ reside)
# - $TARGET, $OUT, $CC, $CFLAGS, $LDFLAGS, $LIBS are set
# - $HARNESS_DIR is the path to this directory
##

RAW_CC="clang"

SUPPORT="$TARGET/traffic/support"
RUNTIME="$OUT/runtime.o"
$RAW_CC -I"$SUPPORT" -c "$SUPPORT/runtime.c" -o "$RUNTIME"

for HARNESS in "$HARNESS_DIR"/*.c; do
  NAME=$(basename "$HARNESS" .c)
  echo "building $NAME"
  $RAW_CC -Iinclude/ -I"$TARGET/src/" -I"$SUPPORT" -c "$HARNESS" -o "$OUT/$NAME.o"
  $CC "$OUT/$NAME.o" "$RUNTIME" \
    -Wl,--whole-archive .libs/libxml2.a -Wl,--no-whole-archive \
    -o "$OUT/$NAME" -llzma -lz -lm \
    $LDFLAGS $LIBS
done
