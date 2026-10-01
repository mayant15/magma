#!/usr/bin/env bash

set -euo pipefail

pull() {
  FROM="$1"

  FLARE="/mnt/ubuntu/FLARE"

  ssh -v $FROM "cd /mnt/ubuntu && tar -cvzf $FROM.tar.gz FLARE"
  scp -v "$FROM:/mnt/ubuntu/$FROM.tar.gz" .
}

pull svivum-1
pull svivum-2
pull svivum-3
pull svivum-4
pull svivum-5
pull svivum-6
pull svivum-7
pull svivum-8
pull svivum-9
pull svivum-10
