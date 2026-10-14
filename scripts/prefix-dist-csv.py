#!/usr/bin/env python3
"""Build the prefix-distribution CSV from campaign $SHARED directories.

The traffic/ogharn harnesses bump a counter in $SHARED/prefix_counts (64 x
uint64): slot i = executions dispatched to candidate i (index % NUM_CANDIDATES),
slot 63 = executions whose 4-byte prefix was non-zero.

Each ROOT is a captain workdir (or any directory): it is searched recursively
for `prefix_counts` files laid out as <...>/<fuzzer>/<target>/<program>/<n>/,
which is how captain names a campaign's $SHARED (under cache/ while running,
under ar/ once finished; ar/ wins if both exist). A single $SHARED outside that
layout can be given with --target and --program.

usage: prefix-dist-csv.py [--magma DIR] [--harnesses traffic] [--out FILE]
                          [--target T --program P] ROOT [ROOT ...]
"""
import argparse
import os
import re
import struct
import sys

ap = argparse.ArgumentParser()
ap.add_argument("roots", nargs="+")
ap.add_argument("--magma", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), ".."))
ap.add_argument("--harnesses", default="traffic", help="harness dir under targets/<target>/")
ap.add_argument("--out", default="-")
ap.add_argument("--target")
ap.add_argument("--program")
args = ap.parse_args()

found = {}  # (target, program, repeat) -> (is_archived, path)
for root in args.roots:
    for dirpath, _, files in os.walk(root):
        if "prefix_counts" not in files:
            continue
        parts = os.path.abspath(dirpath).split(os.sep)
        if args.target and args.program:
            target, program, repeat = args.target, args.program, parts[-1]
        else:
            target, program, repeat = parts[-3], parts[-2], parts[-1]
        archived = "ar" in parts
        key = (target, program, repeat)
        if key not in found or (archived and not found[key][0]):
            found[key] = (archived, os.path.join(dirpath, "prefix_counts"))

rows = ["lib,program,repeat,num_candidates,total_execs,nonzero_prefix_execs,candidate_counts"]
for (target, program, repeat), (_, path) in sorted(found.items()):
    src = os.path.join(args.magma, "targets", target, args.harnesses, program + ".c")
    try:
        n = int(re.search(r"NUM_CANDIDATES (\d+)", open(src).read()).group(1))
    except (OSError, AttributeError):
        sys.exit(f"cannot read NUM_CANDIDATES from {src}")
    c = struct.unpack("64Q", open(path, "rb").read(512))
    rows.append(f"{target},{program},{repeat},{n},{sum(c[:63])},{c[63]},{' '.join(map(str, c[:n]))}")

text = "\n".join(rows) + "\n"
if args.out == "-":
    sys.stdout.write(text)
else:
    open(args.out, "w").write(text)
print(f"{len(rows) - 1} campaigns", file=sys.stderr)
