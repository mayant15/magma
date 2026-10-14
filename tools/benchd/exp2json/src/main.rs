use std::collections::{BTreeMap, BTreeSet};
use std::fs;
use std::io::{self, Read, Write};
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicU8, Ordering};

use anyhow::{anyhow, Context, Result};
use clap::Parser;
use rayon::prelude::*;
use serde_json::json;

/// Collects data from the experiment workdir and outputs a summary as a JSON file.
#[derive(Parser)]
#[command(about = "Collects data from the experiment workdir and outputs a summary as a JSON file.")]
struct Args {
    /// The number of concurrent threads to launch. Defaults depend on
    /// --time-to-bug: that mode reads every monitor dump file (latency-bound
    /// cold I/O, so it wants far more threads than CPU cores), while the
    /// default mode reads only one file per campaign (cheap either way).
    #[arg(long)]
    workers: Option<usize>,

    /// Also compute per-bug first-reached/first-triggered timestamps by
    /// scanning every monitor dump file in each campaign, not just the
    /// latest one. Slower — potentially much slower on large campaigns,
    /// since it reads every cold file on disk instead of just one.
    #[arg(long)]
    time_to_bug: bool,

    /// The path to the Captain tool output workdir.
    workdir: PathBuf,

    /// The file to which the output will be written, or - for stdout.
    outfile: String,

    /// Reduces the verbosity of messages. -q hides info (warnings and higher
    /// only). -qq hides warnings too (errors only). Default: info and higher.
    #[arg(short, long, action = clap::ArgAction::Count)]
    quiet: u8,
}

const INFO: u8 = 0;
const WARNING: u8 = 1;
const ERROR: u8 = 2;

static LOG_THRESHOLD: AtomicU8 = AtomicU8::new(INFO);

fn log_at(level: u8, label: &str, msg: &str) {
    if level >= LOG_THRESHOLD.load(Ordering::Relaxed) {
        eprintln!("{}:exp2json:{}", label, msg);
    }
}

macro_rules! info_log {
    ($($arg:tt)*) => { log_at(INFO, "INFO", &format!($($arg)*)) };
}
macro_rules! warn_log {
    ($($arg:tt)*) => { log_at(WARNING, "WARNING", &format!($($arg)*)) };
}
macro_rules! error_log {
    ($($arg:tt)*) => { log_at(ERROR, "ERROR", &format!($($arg)*)) };
}

fn configure_verbosity(quiet: u8) {
    let threshold = INFO.saturating_add(quiet).min(ERROR);
    LOG_THRESHOLD.store(threshold, Ordering::Relaxed);
}

/// A single fuzzer/target/program/run campaign discovered under `<workdir>/ar`.
struct Campaign {
    path: PathBuf,
    fuzzer: String,
    target: String,
    program: String,
    run: String,
}

fn list_subdirs(dir: &Path) -> Result<Vec<String>> {
    let mut out = Vec::new();
    for entry in fs::read_dir(dir).with_context(|| format!("reading directory {}", dir.display()))? {
        let entry = entry?;
        if entry.file_type()?.is_dir() {
            out.push(entry.file_name().to_string_lossy().into_owned());
        }
    }
    Ok(out)
}

fn find_campaigns(workdir: &Path) -> Result<Vec<Campaign>> {
    let ar_dir = workdir.join("ar");
    if !ar_dir.is_dir() {
        return Err(anyhow!("{} is not a directory", ar_dir.display()));
    }

    let mut campaigns = Vec::new();
    for fuzzer in list_subdirs(&ar_dir)? {
        let fuzzer_dir = ar_dir.join(&fuzzer);
        for target in list_subdirs(&fuzzer_dir)? {
            let target_dir = fuzzer_dir.join(&target);
            for program in list_subdirs(&target_dir)? {
                let program_dir = target_dir.join(&program);
                for run in list_subdirs(&program_dir)? {
                    if run.is_empty() || !run.chars().all(|c| c.is_ascii_digit()) {
                        warn_log!(
                            "Detected invalid workdir hierarchy! Make sure to point \
                             the script to the root of the original workdir."
                        );
                    }
                    campaigns.push(Campaign {
                        path: program_dir.join(&run),
                        fuzzer: fuzzer.clone(),
                        target: target.clone(),
                        program: program.clone(),
                        run,
                    });
                }
            }
        }
    }
    Ok(campaigns)
}

/// Reads monitor dump files directly out of a tarball, without ever
/// extracting to disk. Only entries found under a path component literally
/// named "monitor" are considered; non-numeric names (besides the stray
/// "tmp" entry) are silently skipped. Errors only if no "monitor" path
/// component is found anywhere in the archive.
fn collect_from_tar(tarball: &Path) -> Result<Vec<(u64, String)>> {
    let file = fs::File::open(tarball).with_context(|| format!("opening {}", tarball.display()))?;
    let mut archive = tar::Archive::new(file);

    let mut out = Vec::new();
    let mut monitor_seen = false;

    for entry_res in archive.entries().with_context(|| format!("reading tar {}", tarball.display()))? {
        let mut entry = entry_res?;
        let is_dir = entry.header().entry_type().is_dir();
        let path = entry.path()?.into_owned();
        let comps: Vec<_> = path.components().collect();

        let Some(idx) = comps.iter().position(|c| c.as_os_str() == "monitor") else {
            continue;
        };
        monitor_seen = true;

        let rest = &comps[idx + 1..];
        if is_dir || rest.len() != 1 {
            continue;
        }
        let Some(ts) = rest[0].as_os_str().to_str().and_then(|s| s.parse::<u64>().ok()) else {
            continue;
        };

        let mut content = String::new();
        entry.read_to_string(&mut content)?;
        out.push((ts, content));
    }

    if !monitor_seen {
        return Err(anyhow!("no monitor directory found in {}", tarball.display()));
    }
    Ok(out)
}

fn parse_numeric(s: &str) -> i64 {
    let s = s.trim();
    if let Ok(v) = s.parse::<i64>() {
        return v;
    }
    if let Ok(v) = s.parse::<f64>() {
        return v.trunc() as i64;
    }
    0
}

/// Parses a single monitor dump file's header + first data row into
/// (column, value) pairs. Returns None if the file has no data row (e.g. a
/// dump caught mid-write), mirroring the original script skipping a
/// `StopIteration` from `csv.DictReader`.
fn parse_row(content: &str) -> Option<Vec<(String, i64)>> {
    let mut lines = content.lines();
    let header = lines.next()?;
    let data = lines.next()?;

    let cols: Vec<&str> = header.split(',').collect();
    let vals: Vec<&str> = data.split(',').collect();
    let n = cols.len().min(vals.len());

    let mut out = Vec::with_capacity(n);
    for i in 0..n {
        out.push((cols[i].trim().to_string(), parse_numeric(vals[i])));
    }
    Some(out)
}

enum CampaignResult {
    /// Default mode: just which bugs were ever reached/triggered, read from
    /// a single (the most recent readable) monitor dump per campaign.
    BugsOnly {
        reached: BTreeSet<String>,
        triggered: BTreeSet<String>,
    },
    /// --time-to-bug mode: first-positive timestamp per bug, scanning every
    /// monitor dump file in the campaign.
    WithTimes {
        reached: BTreeMap<String, u64>,
        triggered: BTreeMap<String, u64>,
    },
}

impl CampaignResult {
    fn empty_bugs_only() -> Self {
        CampaignResult::BugsOnly {
            reached: BTreeSet::new(),
            triggered: BTreeSet::new(),
        }
    }

    fn empty_with_times() -> Self {
        CampaignResult::WithTimes {
            reached: BTreeMap::new(),
            triggered: BTreeMap::new(),
        }
    }

    fn to_json(&self) -> serde_json::Value {
        match self {
            CampaignResult::BugsOnly { reached, triggered } => json!({
                "reached": reached,
                "triggered": triggered,
            }),
            CampaignResult::WithTimes { reached, triggered } => json!({
                "reached": reached,
                "triggered": triggered,
            }),
        }
    }
}

fn bugs_from_row(row: Vec<(String, i64)>) -> (BTreeSet<String>, BTreeSet<String>) {
    let mut reached = BTreeSet::new();
    let mut triggered = BTreeSet::new();
    for (col, val) in row {
        if val <= 0 {
            continue;
        }
        if let Some(bug) = col.strip_suffix("_R") {
            reached.insert(bug.to_string());
        } else if let Some(bug) = col.strip_suffix("_T") {
            triggered.insert(bug.to_string());
        }
    }
    (reached, triggered)
}

/// Finds the most recent *readable* monitor dump in a plain directory (the
/// highest numeric filename whose header+data row actually parses — a dump
/// can be caught mid-write and need falling back to the next-most-recent
/// one) and returns its parsed row. `Ok(None)` means the directory exists
/// but has no usable dump at all. Canary counters are monotonically
/// cumulative, so the latest dump's positive columns are exactly the set of
/// bugs ever reached/triggered up to that point.
fn best_dir_row(dir: &Path) -> Result<Option<Vec<(String, i64)>>> {
    if !dir.is_dir() {
        return Err(anyhow!("monitor directory {} does not exist", dir.display()));
    }
    let mut candidates: Vec<(u64, PathBuf)> = Vec::new();
    for entry in fs::read_dir(dir).with_context(|| format!("reading directory {}", dir.display()))? {
        let entry = entry?;
        if entry.file_name() == "tmp" {
            continue;
        }
        if let Some(ts) = entry.file_name().to_str().and_then(|s| s.parse::<u64>().ok()) {
            candidates.push((ts, entry.path()));
        }
    }
    candidates.sort_unstable_by_key(|(ts, _)| std::cmp::Reverse(*ts));

    for (_, path) in candidates {
        let content = fs::read_to_string(&path)
            .with_context(|| format!("reading monitor file {}", path.display()))?;
        if let Some(row) = parse_row(&content) {
            return Ok(Some(row));
        }
        info_log!("Truncated monitor file contains no rows! ({})", path.display());
    }
    Ok(None)
}

/// Tarball equivalent of `best_dir_row`: reads the archive once (cheap,
/// sequential), then picks the most recent readable entry.
fn best_tar_row(tarball: &Path) -> Result<Option<Vec<(String, i64)>>> {
    let mut entries = collect_from_tar(tarball)?;
    entries.sort_unstable_by_key(|(ts, _)| std::cmp::Reverse(*ts));
    for (_, content) in entries {
        if let Some(row) = parse_row(&content) {
            return Ok(Some(row));
        }
        info_log!("Truncated monitor file contains no rows!");
    }
    Ok(None)
}

struct ProcessedCampaign {
    fuzzer: String,
    target: String,
    program: String,
    run: String,
    result: Option<CampaignResult>,
}

fn campaign_name(c: &Campaign) -> String {
    format!("{}/{}/{}/{}", c.fuzzer, c.target, c.program, c.run)
}

fn no_monitor_logs_warning(workdir: &Path, name: &str) {
    let logfile = workdir
        .join("log")
        .join(format!("{}_container.log", name.replace('/', "_")));
    warn_log!(
        "{} contains no monitor logs. Check the corresponding campaign \
         log file for more information: {}",
        name,
        logfile.display()
    );
}

/// Default (fast) path: read only the most recent readable monitor dump per
/// campaign.
fn process_campaign_bugs_only(workdir: &Path, c: &Campaign) -> ProcessedCampaign {
    let name = campaign_name(c);
    info_log!("Processing {}", c.path.display());

    let tarball = c.path.join("ball.tar");
    let row_result = if tarball.is_file() {
        best_tar_row(&tarball)
    } else {
        best_dir_row(&c.path.join("monitor"))
    };

    let result = match row_result {
        Ok(Some(row)) => {
            let (reached, triggered) = bugs_from_row(row);
            Some(CampaignResult::BugsOnly { reached, triggered })
        }
        Ok(None) => {
            no_monitor_logs_warning(workdir, &name);
            Some(CampaignResult::empty_bugs_only())
        }
        Err(e) => {
            error_log!("Encountered exception when processing {}. Details: {}", name, e);
            None
        }
    };

    ProcessedCampaign {
        fuzzer: c.fuzzer.clone(),
        target: c.target.clone(),
        program: c.program.clone(),
        run: c.run.clone(),
        result,
    }
}

/// A campaign's monitor data before file *contents* have been read, used
/// only by --time-to-bug mode. Tarballs are read fully up front (one
/// sequential stream — no per-file random I/O, so there's nothing to gain
/// from spreading it out). Plain directories instead yield just a list of
/// paths: reading many cold files one at a time is latency-bound rather
/// than CPU-bound (each open+read pays for a random I/O round trip), so
/// actually reading them is deferred and flattened across *every* campaign
/// into one pool — that lets concurrency scale with total file count
/// instead of being capped by campaign count or by one thread serially
/// draining a single campaign's directory.
enum CampaignFiles {
    Ready(Result<Vec<(u64, String)>>),
    Pending(Result<Vec<(u64, PathBuf)>>),
}

fn gather_campaign_for_ttb(c: &Campaign) -> CampaignFiles {
    info_log!("Processing {}", c.path.display());

    let tarball = c.path.join("ball.tar");
    if tarball.is_file() {
        CampaignFiles::Ready(collect_from_tar(&tarball))
    } else {
        CampaignFiles::Pending(list_monitor_files(&c.path.join("monitor")))
    }
}

/// Lists monitor dump files to read (as (timestamp, path) pairs), without
/// opening any of them. Errors if the directory itself is missing entirely
/// (as opposed to present but empty), or if any filename besides the stray
/// "tmp" entry isn't purely numeric — mirroring Python's `sort(key=int)`
/// raising on the same input.
fn list_monitor_files(dir: &Path) -> Result<Vec<(u64, PathBuf)>> {
    if !dir.is_dir() {
        return Err(anyhow!("monitor directory {} does not exist", dir.display()));
    }
    let mut out = Vec::new();
    for entry in fs::read_dir(dir).with_context(|| format!("reading directory {}", dir.display()))? {
        let entry = entry?;
        let name = entry.file_name();
        if name == "tmp" {
            continue;
        }
        let ts: u64 = name
            .to_string_lossy()
            .parse()
            .with_context(|| format!("invalid monitor dump filename '{}'", name.to_string_lossy()))?;
        out.push((ts, entry.path()));
    }
    Ok(out)
}

fn compute_ttb(mut files: Vec<(u64, String)>) -> CampaignResult {
    files.sort_unstable_by_key(|(ts, _)| *ts);
    let mut reached = BTreeMap::new();
    let mut triggered = BTreeMap::new();
    for (ts, content) in files {
        let Some(row) = parse_row(&content) else {
            info_log!("Truncated monitor file contains no rows!");
            continue;
        };
        for (col, val) in row {
            if val <= 0 {
                continue;
            }
            if let Some(bug) = col.strip_suffix("_R") {
                reached.entry(bug.to_string()).or_insert(ts);
            } else if let Some(bug) = col.strip_suffix("_T") {
                triggered.entry(bug.to_string()).or_insert(ts);
            }
        }
    }
    CampaignResult::WithTimes { reached, triggered }
}

fn finalize_campaign_ttb(workdir: &Path, c: &Campaign, raw: Result<Vec<(u64, String)>>) -> ProcessedCampaign {
    let name = campaign_name(c);

    let result = match raw {
        Ok(files) if files.is_empty() => {
            no_monitor_logs_warning(workdir, &name);
            Some(CampaignResult::empty_with_times())
        }
        Ok(files) => Some(compute_ttb(files)),
        Err(e) => {
            error_log!("Encountered exception when processing {}. Details: {}", name, e);
            None
        }
    };

    ProcessedCampaign {
        fuzzer: c.fuzzer.clone(),
        target: c.target.clone(),
        program: c.program.clone(),
        run: c.run.clone(),
        result,
    }
}

/// --time-to-bug path: scans every monitor dump file across every
/// campaign, flattened into one pool so read concurrency scales with total
/// file count rather than campaign count.
fn process_campaigns_ttb(workdir: &Path, campaigns: &[Campaign]) -> Vec<ProcessedCampaign> {
    let gathered: Vec<CampaignFiles> = campaigns.par_iter().map(gather_campaign_for_ttb).collect();

    let mut raw: Vec<Result<Vec<(u64, String)>>> = Vec::with_capacity(gathered.len());
    let mut pending: Vec<(usize, u64, PathBuf)> = Vec::new();
    for (i, g) in gathered.into_iter().enumerate() {
        match g {
            CampaignFiles::Ready(r) => raw.push(r),
            CampaignFiles::Pending(Ok(files)) => {
                pending.extend(files.into_iter().map(|(ts, p)| (i, ts, p)));
                raw.push(Ok(Vec::new()));
            }
            CampaignFiles::Pending(Err(e)) => raw.push(Err(e)),
        }
    }

    let read_results: Vec<(usize, Result<(u64, String)>)> = pending
        .into_par_iter()
        .map(|(i, ts, path)| {
            let result = fs::read_to_string(&path)
                .map(|content| (ts, content))
                .with_context(|| format!("reading monitor file {}", path.display()));
            (i, result)
        })
        .collect();

    for (i, result) in read_results {
        let slot = &mut raw[i];
        match result {
            Ok(entry) => {
                if let Ok(v) = slot {
                    v.push(entry);
                }
            }
            Err(e) => *slot = Err(e),
        }
    }

    campaigns
        .par_iter()
        .zip(raw.into_par_iter())
        .map(|(c, r)| finalize_campaign_ttb(workdir, c, r))
        .collect()
}

fn main() -> Result<()> {
    let args = Args::parse();
    configure_verbosity(args.quiet);

    let workers = args.workers.unwrap_or(if args.time_to_bug { 64 } else { 8 });
    rayon::ThreadPoolBuilder::new()
        .num_threads(workers)
        .build_global()
        .context("building thread pool")?;

    let campaigns = find_campaigns(&args.workdir)?;

    let processed: Vec<ProcessedCampaign> = if args.time_to_bug {
        process_campaigns_ttb(&args.workdir, &campaigns)
    } else {
        campaigns
            .par_iter()
            .map(|c| process_campaign_bugs_only(&args.workdir, c))
            .collect()
    };

    let mut results: BTreeMap<String, BTreeMap<String, BTreeMap<String, BTreeMap<String, serde_json::Value>>>> =
        BTreeMap::new();

    for pc in processed {
        let name = format!("{}/{}/{}/{}", pc.fuzzer, pc.target, pc.program, pc.run);
        match pc.result {
            Some(r) => {
                results
                    .entry(pc.fuzzer)
                    .or_default()
                    .entry(pc.target)
                    .or_default()
                    .entry(pc.program)
                    .or_default()
                    .insert(pc.run, r.to_json());
            }
            None => {
                warn_log!("{} has been omitted!", name);
            }
        }
    }

    let output = json!({ "results": results });
    let data = serde_json::to_vec(&output)?;

    if args.outfile == "-" {
        io::stdout().write_all(&data)?;
    } else {
        fs::write(&args.outfile, &data)
            .with_context(|| format!("writing output to {}", args.outfile))?;
    }

    Ok(())
}
