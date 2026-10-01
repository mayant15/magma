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

pull svivum-2 traffic/libxml2.tar.gz
pull svivum-3 traffic/libpng.tar.gz
pull svivum-4 traffic/libsndfile.tar.gz
pull svivum-5 traffic/libtiff.tar.gz
pull svivum-6 traffic/openssl.tar.gz
pull svivum-7 traffic/lua.tar.gz
pull svivum-8 traffic/sqlite3.tar.gz
