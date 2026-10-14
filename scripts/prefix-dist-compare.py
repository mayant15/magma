#!/usr/bin/env python3
"""Compare zero-prefix vs spread-prefix runs (results/prefix-dist{,-spread}.csv) -> results/prefix-dist-compare.md.
Campaigns with < 1000 executions (AFL++ aborted in its seed dry run) are excluded and counted."""
import csv, collections, math, os
R = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "results")
excluded = collections.Counter()

def load(p):
    g = collections.defaultdict(list)
    for r in csv.DictReader(open(p)):
        if int(r["total_execs"]) < 1000:
            excluded[(p, r["lib"], r["program"].startswith("harness_base"))] += 1
            continue
        c = list(map(int, r["candidate_counts"].split())); tot = sum(c)
        p_ = [x / tot for x in c if x]
        ent = -sum(x * math.log(x) for x in p_) / math.log(len(c)) if len(c) > 1 else 1.0
        g[(r["lib"], "harness_base_N" if r["program"].startswith("harness_base") else "harness_N")].append(
            (int(r["total_execs"]), int(r["nonzero_prefix_execs"]), max(c) / tot, ent, min(c) / tot * len(c)))
    return g
a, b = load(R + "/prefix-dist.csv"), load(R + "/prefix-dist-spread.csv")
m = lambda v, i: sum(x[i] for x in v) / len(v)
out = ["# Prefix distribution: zero-prefix seeds vs spread-prefix seeds", "",
"Both: traffic harnesses, AFL++, 5 min x 2 repeats per program. *zero* = all seeds start with `00 00 00 00` (`prefix-dist.csv`); *spread* = seed j gets prefix `j % K` (`scripts/spread-prefix.py`, `prefix-dist-spread.csv`), K = max `NUM_CANDIDATES` of the library's traffic harnesses.", "",
"Evenness = normalized Shannon entropy of per-campaign candidate counts (1.0 = uniform; mean over campaigns). Top share = share of the most-executed candidate (mean). Min/uniform = least-executed candidate's share divided by 1/N (mean; 1.0 = uniform, 0 = a candidate starved). Execs = total executions (throughput proxy).", "",
"| lib | harnesses | evenness zero → spread | top share zero → spread | min/uniform zero → spread | execs zero → spread |",
"|---|---|---:|---:|---:|---:|"]
for k in sorted(a):
    if k not in b: continue
    x, y = a[k], b[k]
    out.append(f"| {k[0]} | {k[1]} | {m(x,3):.2f} → {m(y,3):.2f} | {100*m(x,2):.0f}% → {100*m(y,2):.0f}% | {m(x,4):.2f} → {m(y,4):.2f} | {sum(v[0] for v in x)/1e6:.1f}M → {sum(v[0] for v in y)/1e6:.1f}M |")
ex = sorted({(l, "harness_base_N" if base else "harness_N", n) for (p, l, base), n in excluded.items()})
if ex:
    out += ["", "Excluded (AFL++ aborted in the dry run, < 1000 execs): " + "; ".join(f"{l} {h}: {n} campaigns" for l, h, n in ex) + ". In the spread run, lua seeds `vararg.lua`, `sort.lua`, `pm.lua` timed out when routed to some `harness_base_*` candidates."]
open(R + "/prefix-dist-compare.md", "w").write("\n".join(out) + "\n")
print("\n".join(out[8:]))
