#!/usr/bin/env bash
# Prepend 4 zero bytes to every regular file in a directory (in-place).
set -euo pipefail

dir="${1:-.}"

if [[ ! -d "$dir" ]]; then
    echo "Not a directory: $dir" >&2
    exit 1
fi

for f in "$dir"/*; do
    [[ -f "$f" ]] || continue
    tmp="$(mktemp "$(dirname "$f")/.prepend.XXXXXX")"
    printf '\x00\x00\x00\x00' > "$tmp"
    cat "$f" >> "$tmp"
    mv "$tmp" "$f"
done
