# Magma: A Ground-Truth Fuzzing Benchmark

The documentation has been moved to [the Magma homepage](https://hexhive.epfl.ch/magma).

## Custom Harnesses

This fork adds support for fuzzing with custom harnesses. Keeps harnesses in `targets/`
alongside other target scripts, then specify `<fuzzer>_HARNESSES` in your `captainrc`.

For example, `targets/libpng/custom` has two sample harnesses for AFL++.

> NOTE: Custom harness support is limited to C harnesses and AFL++.

Build with the following `captainrc`:
```bash
FUZZERS=(aflplusplus)
aflplusplus_TARGETS=(libpng)
aflplusplus_HARNESSES=(custom)
aflplusplus_HARNESS_ARGS="@@"
```

`<fuzzer>_HARNESS_ARGS` sets default program arguments for all custom harness
programs (used only when `$HARNESSES` is set and no per-program `_ARGS` is found
in the target's `configrc`). This is useful for file-input harnesses that read
from `argv[1]` — set `"@@"` so the fuzzer substitutes the input file path.

### Adding Custom Harnesses

1. Create a directory under `targets/<TARGET>/` for your harness set (e.g. `targets/<TARGET>/ogharn/`).
2. Add harness source files (`*.c`) to that directory.
3. Add a `build.sh` to that directory with harness-specific build instructions. It is sourced by the target's `build.sh` and inherits the same environment (`$OUT`, `$CC`, `$CFLAGS`, `$LDFLAGS`, `$LIBS`, `$HARNESS_DIR`, CWD at `$TARGET/repo`). If no `build.sh` is present, a default recipe that links against the Traffic runtime is used.

See `targets/libxml2/ogharn/build.sh` and `targets/libxml2/traffic/build.sh` for reference.

Target build scripts receive the `$HARNESSES` environment variable, which is the value set in
`captainrc` with `<fuzzer>_HARNESSES=(...)`.

### Seeds

This fork adds support for _"default"_ seeds:
1. First check if `$TARGET/corpus/$PROGRAM` exists. If so, use that.
1. Otherwise use `$TARGET/corpus/default`.

This is so we don't have to duplicate seeds N times for all N harnesses we might generate.
