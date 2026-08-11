##
# Build script for ogharn standalone file-input harnesses.
#
# These harnesses define main() and read input from a file path in argv[1].
# They do not use the Traffic runtime or its FuzzedDataProvider.
#
# Sourced by targets/libxml2/build.sh — inherits its environment:
# - CWD is $TARGET/repo (where .libs/libxml2.a and include/ reside)
# - $TARGET, $OUT, $CC, $CFLAGS, $LDFLAGS, $LIBS are set
# - $HARNESS_DIR is the path to this directory
##

RAW_CC="clang"

for HARNESS in "$HARNESS_DIR"/*.c; do
  NAME=$(basename "$HARNESS" .c)
  echo "building $NAME"
  $RAW_CC -Iinclude/ -I"$TARGET/src/" -c "$HARNESS" -o "$OUT/$NAME.o"
  $CC "$OUT/$NAME.o" \
    -Wl,--whole-archive .libs/libxml2.a -Wl,--no-whole-archive \
    -o "$OUT/$NAME" -llzma -lz -lm \
    $LDFLAGS $LIBS
done
