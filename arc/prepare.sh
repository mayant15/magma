#!/usr/bin/env bash

FUZZER=aflplusplus
TARGETS=(
  libpng
)

# https://stackoverflow.com/a/246128
ARC_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
MAGMA_DIR=$(realpath "$ARC_DIR/.." )

if [[ ! $MAGMA_DIR -ef $PWD ]]; then
  echo "error: must run prepare.sh from magma repository root"
  exit 1
fi

PACKAGE_DIR="$ARC_DIR/package"

mkdir -p $PACKAGE_DIR

if [[ ! -f "$PACKAGE_DIR/base.sif" ]]; then
  apptainer build \
    --build-arg fuzzer=$FUZZER \
    "$PACKAGE_DIR/base.sif" "$ARC_DIR/base.def"
else
  echo "using existing base image"
fi

for TARGET in "${TARGETS[@]}"; do
  SIF="$PACKAGE_DIR/magma_${FUZZER}_${TARGET}.sif"

  # TODO: how do we control other build args from captainrc?
  apptainer build \
    --build-arg target=$TARGET \
    --build-arg fuzzer=$FUZZER \
    "$PACKAGE_DIR/magma_aflplusplus_$TARGET.sif" "$ARC_DIR/final.def"
done
