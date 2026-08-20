#!/bin/bash -e

##
# Pre-requirements:
# - env FUZZER: fuzzer name (from fuzzers/)
# - env TARGET: target name (from targets/)
# + env MAGMA: path to magma root (default: ../../)
# + env HARNESSES: path to custom harnesses (default: unset)
# + env ISAN: if set, build the benchmark with ISAN/fatal canaries (default: unset)
# + env HARDEN: if set, build the benchmark with hardened canaries (default: unset)
# + env ARC: if set, build Apptainer containers for ARC instead of Docker (default: unset)
##

if [ -z $FUZZER ] || [ -z $TARGET ]; then
    echo '$FUZZER and $TARGET must be specified as environment variables.'
    exit 1
fi
IMG_NAME="magma/$FUZZER/$TARGET"
MAGMA=${MAGMA:-"$(cd "$(dirname "${BASH_SOURCE[0]}")/../../" >/dev/null 2>&1 \
    && pwd)"}
source "$MAGMA/tools/captain/common.sh"

CANARY_MODE=${CANARY_MODE:-1}

case $CANARY_MODE in
1)
    mode_flag="--build-arg canaries=1"
    ;;
2)
    mode_flag=""
    ;;
3)
    mode_flag="--build-arg fixes=1"
    ;;
esac

if [ ! -z $ISAN ]; then
    isan_flag="--build-arg isan=1"
fi
if [ ! -z $HARDEN ]; then
    harden_flag="--build-arg harden=1"
fi
if [ ! -z $HARNESSES ]; then
  harness_flag="--build-arg HARNESSES=$HARNESSES"
fi

set -x

if [ ! -z $ARC ]; then
  pushd $MAGMA

  PACKAGE="$MAGMA/arc/package"
  mkdir -p $PACKAGE

  BASE_SIF="$PACKAGE/base.sif"
  if [ ! -f $BASE_SIF ]; then
    apptainer build \
      --build-arg fuzzer="$FUZZER" \
      $BASE_SIF "$MAGMA/arc/base.def"
  fi

  SIF="arc/package/magma_${FUZZER}_${TARGET}.sif"
  if [ -z $FORCE_REBUILD ] && [ -f "$SIF" ]; then
    echo "Reusing existing image: $SIF"
  else
    apptainer build \
      --force \
      --build-arg fuzzer="$FUZZER" \
      --build-arg target="$TARGET" \
      $mode_flag $isan_flag $harden_flag $harness_flag \
      $SIF "$MAGMA/arc/final.def"
  fi

  popd
else
  # TODO(Mayant): Should we pass in GROUP_ID and USER_ID?
  docker build -t "$IMG_NAME" \
      --build-arg fuzzer_name="$FUZZER" \
      --build-arg target_name="$TARGET" \
      $mode_flag $isan_flag $harden_flag $harness_flag \
      -f "$MAGMA/docker/Dockerfile" "$MAGMA"
fi

set +x

echo "$IMG_NAME"
