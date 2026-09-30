#!/usr/bin/env bash

# Pull Magma working directories from svivum machines

set -euo pipefail

# Usage: pull-workdir.sh <ssh-remote> <out-name>

pull() {
  FROM="$1"
  TO="$2"
  

  CAPTAIN="/mnt/ubuntu/traffic/magma/tools/captain/"
  OUT="$CAPTAIN/workdir.tar.gz"

  ssh -v $FROM "cd $CAPTAIN && tar -cvzf workdir.tar.gz workdir"
  scp -v "$FROM:$OUT" "$TO"
}

pull svivum-9 openssl-ogharn.tar.gz
