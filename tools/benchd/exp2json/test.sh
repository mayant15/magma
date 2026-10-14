#!/usr/bin/env bash
# Builds synthetic campaign fixtures (plain monitor dir, tarball, empty
# monitor dir, missing monitor dir, truncated-latest-dump fallback) and
# checks the Rust exp2json against the Python original:
#
#   - `exp2json --time-to-bug` must produce byte-identical JSON (modulo key
#     order) to the Python original, which always scans every dump file.
#   - `exp2json` (default, bugs-only) must agree with Python on exactly
#     which bugs were ever reached/triggered per run, ignoring timestamps
#     (Python's result with each reached/triggered dict reduced to its
#     sorted key list).
#
# Usage: ./test.sh   (run inside `nix develop`, or anywhere with cargo and
#                      python3 on PATH)
set -euo pipefail

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PY_SCRIPT="$HERE/../exp2json.py"

echo "Building release binary..."
(cd "$HERE" && cargo build --release --quiet)
RUST_BIN="$HERE/target/release/exp2json"

WD="$(mktemp -d)"
trap 'rm -rf "$WD"' EXIT

# --- fixture: plain monitor dir, with a stray "tmp" file to be ignored,
# and a truncated latest dump that the default mode must fall back past ---
mkdir -p "$WD/ar/afl/openssl/prog1/0/monitor"
cat > "$WD/ar/afl/openssl/prog1/0/monitor/10" <<'EOF'
bug1_R,bug1_T,bug2_R,bug2_T
0,0,0,0
EOF
cat > "$WD/ar/afl/openssl/prog1/0/monitor/20" <<'EOF'
bug1_R,bug1_T,bug2_R,bug2_T
1,0,0,0
EOF
cat > "$WD/ar/afl/openssl/prog1/0/monitor/30" <<'EOF'
bug1_R,bug1_T,bug2_R,bug2_T
1,1,1,0
EOF
# truncated: header only, no data row (dump caught mid-write)
cat > "$WD/ar/afl/openssl/prog1/0/monitor/40" <<'EOF'
bug1_R,bug1_T,bug2_R,bug2_T
EOF
touch "$WD/ar/afl/openssl/prog1/0/monitor/tmp"

# --- fixture: tarball, with a monitor/tmp/ subdir to be ignored ---
mkdir -p "$WD/ar/afl/openssl/prog1/1"
TARSTAGE="$(mktemp -d)"
mkdir -p "$TARSTAGE/monitor/tmp"
cat > "$TARSTAGE/monitor/5" <<'EOF'
bugA_R,bugA_T
0,0
EOF
cat > "$TARSTAGE/monitor/15" <<'EOF'
bugA_R,bugA_T
1,0
EOF
echo junk > "$TARSTAGE/monitor/tmp/ignoreme"
tar -cf "$WD/ar/afl/openssl/prog1/1/ball.tar" -C "$TARSTAGE" monitor
rm -rf "$TARSTAGE"

# --- fixture: empty monitor dir (zero rows -> warning, still included) ---
mkdir -p "$WD/ar/afl/openssl/prog2/0/monitor"

# --- fixture: missing monitor dir entirely (-> error, omitted) ---
mkdir -p "$WD/ar/afl/openssl/prog2/1"

mkdir -p "$WD/log"

normalize() {
    python3 -c 'import json, sys; print(json.dumps(json.load(sys.stdin), sort_keys=True, indent=2))'
}

# Reduces every {"reached": {bug: ts, ...}, "triggered": {bug: ts, ...}}
# leaf to {"reached": [bug, ...], "triggered": [bug, ...]} (sorted), to
# compare against the default bugs-only mode.
bugs_only_shape() {
    python3 -c '
import json, sys

def walk(node, depth):
    if depth == 4:
        return {k: sorted(v.keys()) for k, v in node.items()}
    return {k: walk(v, depth + 1) for k, v in node.items()}

data = json.load(sys.stdin)
data["results"] = walk(data.get("results", {}), 0)
print(json.dumps(data, sort_keys=True, indent=2))
'
}

echo "Running Python implementation..."
PY_RAW="$(python3 "$PY_SCRIPT" "$WD" - 2>/dev/null)"
PY_JSON="$(echo "$PY_RAW" | normalize)"
PY_BUGS_JSON="$(echo "$PY_RAW" | bugs_only_shape)"

echo "Running Rust implementation (--time-to-bug)..."
RS_TTB_JSON="$("$RUST_BIN" --time-to-bug "$WD" - 2>/dev/null | normalize)"

echo "Running Rust implementation (default, bugs-only)..."
RS_BUGS_JSON="$("$RUST_BIN" "$WD" - 2>/dev/null | normalize)"

ok=1

echo "--- --time-to-bug vs Python (expect identical) ---"
if diff -u <(echo "$PY_JSON") <(echo "$RS_TTB_JSON"); then
    echo "PASS"
else
    echo "FAIL: --time-to-bug output differs from Python." >&2
    ok=0
fi

echo "--- default (bugs-only) vs Python's bug set (expect identical bug names) ---"
if diff -u <(echo "$PY_BUGS_JSON") <(echo "$RS_BUGS_JSON"); then
    echo "PASS"
else
    echo "FAIL: default-mode bug set differs from Python." >&2
    ok=0
fi

if [ "$ok" = 1 ]; then
    echo "ALL TESTS PASSED"
else
    exit 1
fi
