#!/usr/bin/env python3
"""
Merge the standalone, OGHarn-mined harnesses under harnesses/<lib>/out-N/final-harnesses/src/
into per-out-dir dispatcher harnesses under targets/<lib>/ogharn/, following the manual
pattern established in targets/openssl/ogharn/.

For each library:
  - out-1, out-2, out-3 each become one dispatcher: harness_0.c, harness_1.c, harness_2.c
  - within an out-dir, standalone harnesses are sorted NUMERICALLY by their harness
    number (harness1, harness2, ... harness10, ...) and become candidate_0, candidate_1, ...
  - each candidate_K.c keeps everything in the original file before `int main`
    (includes, typedefs, function-pointer stub definitions, etc.) as a prefix, then wraps
    everything after the `fuzzData[size] = '\\0';` boilerplate marker into
    `int fuzz_K(char* fuzzData, long size) { ... }`
  - harness_N.c is the fixed dispatcher template (reads argv[1], takes the first 4 bytes
    as an index, calls fuzz_{index % NUM_CANDIDATES} on the rest), templated only by
    NUM_CANDIDATES and the #include of each candidate_K.c.

This script only writes files under targets/<lib>/ogharn/. It does not touch build.sh,
configrc, or captainrc.

Generated with AI.
"""

import argparse
import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
MARKER_RE = re.compile(r"""fuzzData\[size\] = '\\0';""")
MAIN_RE = re.compile(r"^int\s+main\s*\(")
HARNESS_NUM_RE = re.compile(r"^harness(\d+):")

# OGHarn sometimes emits a `static int function_pointerXYZfp(...)` stub (used as a
# lua_pcallk-style continuation callback) with the *same* name in multiple mined
# harnesses. Since every candidate in an out-dir is #include'd into one dispatcher
# translation unit, identical static names collide at compile time. Detect them per
# candidate and rename to a candidate-unique name.
FUNCTION_POINTER_DEF_RE = re.compile(r"^static\s+[\w\s\*]+?\b(function_pointer\w*)\s*\(")

LIBS = ["libpng", "libsndfile", "libtiff", "libxml2", "lua", "sqlite3", "openssl"]

DISPATCHER_TEMPLATE = """#include <stdint.h>
#include <stdio.h>

{prefix}

#define INT_SIZE 4
#define NUM_CANDIDATES {num_candidates}

int main(int argc, char *argv[])
{{
    FILE *f;
    char *fuzzData = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 1)
        exit(0);

    fuzzData = (char*)malloc((size_t)size+1);
    if(fuzzData == NULL)
        exit(0);

    if(fread(fuzzData, (size_t)size, 1, f) != 1)
        exit(0);
    fuzzData[size] = '\\0';

    if (size < INT_SIZE) return 0;

    uint32_t index = *((uint32_t*)fuzzData);

    char* rest_ptr = fuzzData + INT_SIZE;
    long rest_len = size - INT_SIZE;

    switch (index % NUM_CANDIDATES) {{
{cases}
    }}
}}
"""


def natural_harness_files(src_dir: Path):
    """Return the *.c files in src_dir sorted numerically by harness number."""
    files = list(src_dir.glob("*.c"))
    def key(p: Path):
        m = HARNESS_NUM_RE.match(p.name)
        if not m:
            raise ValueError(f"unexpected filename (no 'harnessN:' prefix): {p.name}")
        return int(m.group(1))
    return sorted(files, key=key)


def split_original(path: Path):
    """Split an original standalone harness into (prefix_before_main, body_after_marker)."""
    text = path.read_text()
    lines = text.splitlines()

    main_idx = None
    for i, line in enumerate(lines):
        if MAIN_RE.match(line):
            main_idx = i
            break
    if main_idx is None:
        raise ValueError(f"no `int main(` found in {path}")

    prefix_lines = lines[:main_idx]
    while prefix_lines and prefix_lines[-1].strip() == "":
        prefix_lines.pop()

    marker_idx = None
    for i, line in enumerate(lines):
        if MARKER_RE.search(line):
            marker_idx = i
            break
    if marker_idx is None:
        raise ValueError(f"no boilerplate marker found in {path}")

    body_lines = lines[marker_idx + 1:]
    while body_lines and body_lines[0].strip() == "":
        body_lines.pop(0)
    if not body_lines:
        raise ValueError(f"empty body after marker in {path}")

    return prefix_lines, body_lines


def rename_colliding_function_pointers(prefix_lines: list, body_lines: list, k: int):
    """Rename any `static ... function_pointerXYZ(...)` stub to a name unique to
    candidate k, rewriting both lines lists in place to match."""
    names = set()
    for line in prefix_lines:
        m = FUNCTION_POINTER_DEF_RE.match(line.strip())
        if m:
            names.add(m.group(1))

    def rename_all(lines):
        for name in names:
            new_name = f"{name}_cand{k}"
            name_re = re.compile(rf"\b{re.escape(name)}\b")
            for i, line in enumerate(lines):
                lines[i] = name_re.sub(new_name, line)

    rename_all(prefix_lines)
    rename_all(body_lines)


def make_candidate(path: Path, k: int) -> str:
    prefix_lines, body_lines = split_original(path)
    rename_colliding_function_pointers(prefix_lines, body_lines, k)
    out = []
    out.extend(prefix_lines)
    out.append("")
    out.append(f"int fuzz_{k}(char* fuzzData, long size) {{")
    out.extend(body_lines)
    text = "\n".join(out)
    if not text.endswith("\n"):
        text += "\n"
    return text


def make_dispatcher(candidate_prefix: list, num_candidates: int) -> str:
    prefix = "\n".join(candidate_prefix)
    cases = "\n".join(
        f"      case {k}: return fuzz_{k}(rest_ptr, rest_len);" for k in range(num_candidates)
    )
    return DISPATCHER_TEMPLATE.format(prefix=prefix, num_candidates=num_candidates, cases=cases)


def process_lib(lib: str, dry_run: bool):
    ogharn_dir = REPO_ROOT / "targets" / lib / "ogharn"
    written = []

    for out_idx in (1, 2, 3):
        harness_idx = out_idx - 1
        src_dir = REPO_ROOT / "harnesses" / lib / f"out-{out_idx}" / "final-harnesses" / "src"
        if not src_dir.is_dir():
            print(f"  [skip] {src_dir} does not exist", file=sys.stderr)
            continue

        files = natural_harness_files(src_dir)
        if not files:
            print(f"  [skip] no harness files in {src_dir}", file=sys.stderr)
            continue

        candidate_dir = ogharn_dir / f"harness_{harness_idx}"
        dispatcher_includes = []
        for k, f in enumerate(files):
            candidate_text = make_candidate(f, k)
            candidate_path = candidate_dir / f"candidate_{k}.c"
            dispatcher_includes.append(f'#include "harness_{harness_idx}/candidate_{k}.c"')
            written.append((candidate_path, candidate_text))

        dispatcher_text = make_dispatcher(dispatcher_includes, len(files))
        dispatcher_path = ogharn_dir / f"harness_{harness_idx}.c"
        written.append((dispatcher_path, dispatcher_text))

    for path, text in written:
        rel = path.relative_to(REPO_ROOT)
        if dry_run:
            print(f"  would write {rel} ({len(text.splitlines())} lines)")
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text)
            print(f"  wrote {rel}")

    return written


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("libs", nargs="*", default=LIBS, help="libraries to process (default: all 6)")
    parser.add_argument("--dry-run", action="store_true", help="print what would be written, without writing")
    parser.add_argument("--clean", action="store_true",
                         help="before writing, remove existing harness_*.c / harness_*/ dirs in targets/<lib>/ogharn/ "
                              "(does NOT touch support/ or build.sh)")
    args = parser.parse_args()

    for lib in args.libs:
        if lib not in LIBS:
            print(f"unknown library: {lib}", file=sys.stderr)
            sys.exit(1)

    for lib in args.libs:
        print(f"== {lib} ==")
        ogharn_dir = REPO_ROOT / "targets" / lib / "ogharn"
        if args.clean and not args.dry_run:
            for p in sorted(ogharn_dir.glob("harness_*")):
                if p.is_dir():
                    for child in sorted(p.glob("*")):
                        child.unlink()
                    p.rmdir()
                else:
                    p.unlink()
                print(f"  removed {p.relative_to(REPO_ROOT)}")
        process_lib(lib, args.dry_run)


if __name__ == "__main__":
    main()
