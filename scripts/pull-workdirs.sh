#!/usr/bin/env bash

# Pull Magma working directories from svivum machines

set -euo pipefail

# Usage: pull-workdir.sh <ssh-remote> <out-name>

pull() {
  FROM="$1"
  TO="$2"
  

  CAPTAIN="/mnt/ubuntu/traffic/magma/tools/captain/"
  OUT="$CAPTAIN/workdir-2026-10-12.tar.gz"

  ssh -v $FROM "cd $CAPTAIN && tar -cvzf workdir-2026-10-12.tar.gz workdir"
  scp -v "$FROM:$OUT" "$TO"
}

pull svivum-1  ogharn/libpng.tar.gz &
pull svivum-2  traffic/libxml2-2.tar.gz &
pull svivum-3  traffic/libsndfile-2.tar.gz &
pull svivum-4  traffic/libtiff-2.tar.gz &
pull svivum-5  traffic/libpng-2.tar.gz &
pull svivum-6  traffic/lua-2.tar.gz &
pull svivum-7  traffic/sqlite3-2.tar.gz &
pull svivum-8  ogharn/libxml2.tar.gz &
pull svivum-9  ogharn/libsndfile.tar.gz &
pull svivum-10 ogharn/libtiff.tar.gz &

wait
