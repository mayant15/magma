#!/usr/bin/env python3
"""Rewrite the 4-byte dispatch prefix of every seed in a directory (in place).

Seed j (sorted by name) gets the little-endian uint32 `j % K`, so that
`index % NUM_CANDIDATES` in the traffic/ogharn harnesses spreads seeds across
candidates instead of sending them all to case 0.

usage: spread-prefix.py <corpus-dir> <K>
"""
import os
import struct
import sys

d, k = sys.argv[1], int(sys.argv[2])
files = sorted(f for f in os.listdir(d) if os.path.isfile(os.path.join(d, f)))
for j, name in enumerate(files):
    path = os.path.join(d, name)
    data = open(path, "rb").read()
    assert len(data) >= 4, path
    open(path, "wb").write(struct.pack("<I", j % k) + data[4:])
print(f"{d}: {len(files)} seeds, prefixes 0..{k - 1}")
