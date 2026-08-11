---
name: running-fuzzing-campaigns
description: >-
  Builds and runs Magma ground-truth fuzzing campaigns using the captain
  toolset, collects results with exp2json.py, and checks for missing logs.
  Use when asked to run fuzzers, build targets, start campaigns, produce
  experiment JSON, or diagnose missing campaign data.
---

# Running Magma Fuzzing Campaigns

Magma is a ground-truth fuzzing benchmark: real libraries with front-ported
bugs and source-level canary instrumentation. The `captain` toolset (in
`tools/captain/`) orchestrates Docker-based builds and campaign execution.
`exp2json.py` (in `tools/benchd/`) collects monitor dumps into a JSON summary.

## Key Files

- `tools/captain/captainrc` — active campaign configuration (sourced as bash)
- `tools/captain/captainrc.old` — full reference for all available options
- `tools/captain/run.sh` — main entry point; builds images and launches campaigns
- `tools/captain/build.sh` — builds a single fuzzer/target Docker image
- `tools/captain/start.sh` — starts a single campaign container
- `tools/captain/common.sh` — shared helpers, loads target `configrc` defaults
- `magma/run.sh` — in-container entrypoint; runs fuzzer + monitor loop
- `tools/benchd/exp2json.py` — collects monitor data from workdir into JSON
- `tools/bugcount.py` — prints reached/triggered bug counts from JSON

## captainrc Configuration

`captainrc` is a bash file sourced by `run.sh`. Key variables:

| Variable | Description | Default |
|---|---|---|
| `WORKDIR` | Root for all output (ar, log, cache, poc, lock) | required |
| `REPEAT` | Number of campaign repetitions per fuzzer/target/program | required |
| `TIMEOUT` | Duration per campaign (suffixes: s, m, h, d) | `1m` |
| `WORKERS` | Number of parallel worker threads | all cores |
| `CAMPAIGN_WORKERS` | CPUs per campaign | `1` |
| `FUZZERS` | Array of fuzzer names (from `fuzzers/`) | required |
| `ISAN` | Set to build with ISAN/fatal canaries | unset |
| `HARDEN` | Set to build with hardened canaries | unset |
| `NO_ARCHIVE` | Set to skip tarballing (keep raw dirs) | unset |
| `CACHE_ON_DISK` | Set to use disk instead of tmpfs for cache | unset |
| `POLL` | Seconds between monitor polls | `5` |
| `CANARY_MODE` | 1=canaries no fixes, 2=no canaries no fixes, 3=fixes no canaries | `1` |
| `POC_EXTRACT` | Set to run extract.sh after campaign | unset |

### Per-fuzzer / per-target overrides

```bash
FUZZERS=(aflplusplus)
aflplusplus_TARGETS=(libpng openssl libtiff)
aflplusplus_HARNESSES=(traffic)          # custom harness subdirectory under each target
aflplusplus_libtiff_PROGRAMS=(tiffcp)    # override programs from target configrc
aflplusplus_libpng_FUZZARGS="-x dict"    # fuzzer-specific args
aflplusplus_CAMPAIGN_WORKERS=2           # override global CAMPAIGN_WORKERS
```

If `fuzzer_TARGETS` is omitted, all targets in `targets/` are used.
If `fuzzer_target_PROGRAMS` is omitted, all programs from the target's
`configrc` are used.

## Available Targets and Programs

Each target has a `configrc` declaring its programs:

| Target | Programs | Notes |
|---|---|---|
| libpng | `libpng_read_fuzzer` | |
| libsndfile | `sndfile_fuzzer` | ARGS=`@@` |
| libtiff | `tiff_read_rgba_fuzzer`, `tiffcp` | tiffcp ARGS=`-M @@ tmp.out` |
| libxml2 | `libxml2_xml_read_memory_fuzzer`, `xmllint` | xmllint ARGS=`--valid --oldxml10 --push --memory @@` |
| lua | `lua` | |
| openssl | `asn1`, `asn1parse`, `bignum`, `server`, `client`, `x509` | |
| php | `json`, `exif`, `unserialize`, `parser` | |
| poppler | `pdf_fuzzer`, `pdfimages`, `pdftoppm` | |
| sqlite3 | `sqlite3_fuzz` | |

## Available Fuzzers

Each fuzzer lives in `fuzzers/<name>/` with `fetch.sh`, `build.sh`,
`instrument.sh`, `run.sh`, `runonce.sh`, `findings.sh`, `preinstall.sh`.

afl, afl_asan, afl_resume, aflfast, moptafl, moptafl_asan, aflplusplus,
aflplusplus_lto, aflplusplus_lto_asan, angora, ddfuzz, eclipser, entropic,
fairfuzz, honggfuzz, honggfuzz_asan, instrim, k_scheduler, klee, libfuzzer,
llvm_analysis, llvm_cov, parmesan, symcc_afl, symcc_analysis, vanilla

## Running a Campaign

### 1. Edit `tools/captain/captainrc`

Set `FUZZERS`, target lists, `REPEAT`, `TIMEOUT`, `WORKERS`.

For a short test run (e.g., 1 repetition, 30-second duration):

```bash
WORKDIR=./workdir
REPEAT=1
TIMEOUT=30s
WORKERS=4
NO_ARCHIVE=1
ISAN=1
FUZZERS=(aflplusplus)
aflplusplus_TARGETS=(libpng openssl libsndfile libtiff libxml2 lua sqlite3)
```

`NO_ARCHIVE=1` is recommended for short runs — it skips tarballing so
`exp2json.py` can read monitor dumps directly from the `ar/` directory.

### 2. Build and run

```bash
cd /home/user/workspace/repo/tools/captain
./run.sh ./captainrc
```

`run.sh` will, for each fuzzer/target:
1. Build the Docker image (`docker build -t magma/<fuzzer>/<target> ...`)
2. For each program, launch `REPEAT` campaign containers in parallel
3. Each container runs `magma/run.sh` which starts the fuzzer and a monitor
   loop that dumps canary status every `POLL` seconds
4. Campaign results are stored under `WORKDIR/ar/<fuzzer>/<target>/<program>/<run>/`
5. Container logs go to `WORKDIR/log/<fuzzer>_<target>_<program>_<run>_container.log`
6. Build logs go to `WORKDIR/log/<fuzzer>_<target>_build.log`

### 3. Collect results with exp2json.py

```bash
python3 tools/benchd/exp2json.py ./workdir -o results.json -v
```

- `./workdir` is the same `WORKDIR` from captainrc
- `-v` prints info (including warnings about campaigns with no monitor logs)
- `-vv` prints debug-level detail
- Output JSON structure: `{"results": {<fuzzer>: {<target>: {<program>: {<run>: {"reached": {...}, "triggered": {...}}}}}}}`

### 4. Summarize bug counts

```bash
python3 tools/bugcount.py results.json
```

Prints a table of reached and triggered bug counts per library.

## Checking for Missing Logs

After a campaign run, check completeness:

1. **Expected runs**: For each fuzzer/target/program combination, there should
   be `REPEAT` numbered directories (0, 1, ..., REPEAT-1) under
   `workdir/ar/<fuzzer>/<target>/<program>/`.

2. **Missing monitor data**: Run `exp2json.py -v` and look for warnings:
   - `"<fuzzer>/<target>/<program>/<run> contains no monitor logs"` — the
     campaign ran but produced no monitor dumps. Check the corresponding
     container log at `workdir/log/<fuzzer>_<target>_<program>_<run>_container.log`.
   - `"<fuzzer>/<target>/<program>/<run> has been omitted!"` — an exception
     occurred during processing.

3. **Missing build**: If a build fails, `run.sh` logs
   `"Failed to build magma/<fuzzer>/<target>"` and skips all programs for that
   target. Check `workdir/log/<fuzzer>_<target>_build.log`.

4. **Quick directory check**: Compare the number of run directories against
   `REPEAT` for each fuzzer/target/program:
   ```bash
   for d in workdir/ar/*/*/*/; do
     count=$(ls -d "$d"*/ 2>/dev/null | wc -l)
     echo "$d: $count runs"
   done
   ```

5. **Monitor files**: Inside each run directory (or tarball `ball.tar`), the
   `monitor/` subdirectory should contain timestamped files (named 0, 5, 10,
   ... incrementing by `POLL`). Empty or missing `monitor/` means the campaign
   didn't run long enough or the fuzzer failed to start.

## Workdir Structure

```
workdir/
├── ar/                  # Campaign archives (results)
│   └── <fuzzer>/
│       └── <target>/
│           └── <program>/
│               └── <run>/       # 0, 1, 2, ...
│                   ├── monitor/  # timestamped canary dump files
│                   ├── log/      # fuzzer stdout/stderr (multilog)
│                   └── findings/ # fuzzer crash/queue outputs
├── cache/               # In-memory tmpfs (or disk) working area
├── log/                 # Container and build logs
├── poc/                 # Proof-of-concept crash files (if POC_EXTRACT)
├── lock/                # Mutex/worker lock files
└── tmp/                 # exp2json.py temporary extraction directory
```

When `NO_ARCHIVE` is unset, each run directory contains `ball.tar` instead
of raw files. `exp2json.py` handles both cases.

## Orb / Sandbox Notes

- Docker must be running: `sudo systemctl start docker` or rely on
  `.agents/setup` / `.agents/resume` which handle Docker installation and
  startup automatically.
- Building Docker images can take significant time (compiling fuzzers and
  targets from source). The `docker/Dockerfile` uses `ubuntu:18.04` as base.
- `run.sh` attempts to mount a tmpfs for `CACHEDIR` by default; set
  `CACHE_ON_DISK=1` in captainrc if sudo mount is unavailable.
- The orb may have limited CPU cores; set `WORKERS` accordingly.
