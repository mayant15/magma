# Prefix distribution: zero-prefix seeds vs spread-prefix seeds

Both: traffic harnesses, AFL++, 5 min x 2 repeats per program. *zero* = all seeds start with `00 00 00 00` (`prefix-dist.csv`); *spread* = seed j gets prefix `j % K` (`scripts/spread-prefix.py`, `prefix-dist-spread.csv`), K = max `NUM_CANDIDATES` of the library's traffic harnesses.

Evenness = normalized Shannon entropy of per-campaign candidate counts (1.0 = uniform; mean over campaigns). Top share = share of the most-executed candidate (mean). Min/uniform = least-executed candidate's share divided by 1/N (mean; 1.0 = uniform, 0 = a candidate starved). Execs = total executions (throughput proxy).

| lib | harnesses | evenness zero → spread | top share zero → spread | min/uniform zero → spread | execs zero → spread |
|---|---|---:|---:|---:|---:|
| libpng | harness_N | 0.37 → 0.26 | 93% → 96% | 0.15 → 0.09 | 3.1M → 2.3M |
| libpng | harness_base_N | 0.77 → 0.70 | 57% → 62% | 0.57 → 0.45 | 3.5M → 2.3M |
| libsndfile | harness_N | 0.65 → 0.78 | 48% → 31% | 0.17 → 0.09 | 2.2M → 1.6M |
| libsndfile | harness_base_N | 0.76 → 0.34 | 71% → 91% | 0.49 → 0.17 | 2.7M → 2.1M |
| libtiff | harness_N | 0.45 → 0.60 | 86% → 72% | 0.18 → 0.18 | 2.5M → 1.8M |
| libtiff | harness_base_N | 0.67 → 0.44 | 51% → 73% | 0.19 → 0.02 | 3.0M → 2.8M |
| libxml2 | harness_N | 0.76 → 0.68 | 48% → 40% | 0.36 → 0.18 | 2.5M → 1.7M |
| libxml2 | harness_base_N | 0.89 → 0.88 | 23% → 29% | 0.33 → 0.48 | 3.4M → 2.1M |
| lua | harness_N | 0.39 → 0.28 | 77% → 82% | 0.05 → 0.03 | 2.8M → 2.2M |
| openssl | harness_N | 0.86 → 0.65 | 61% → 74% | 0.47 → 0.32 | 1.1M → 0.6M |
| openssl | harness_base_N | 0.75 → 0.70 | 47% → 54% | 0.22 → 0.24 | 1.2M → 0.8M |
| sqlite3 | harness_N | 0.72 → 0.81 | 62% → 48% | 0.27 → 0.26 | 2.0M → 1.7M |
| sqlite3 | harness_base_N | 0.93 → 0.92 | 48% → 49% | 0.67 → 0.64 | 2.9M → 2.1M |

Excluded (AFL++ aborted in the dry run, < 1000 execs): lua harness_base_N: 6 campaigns. In the spread run, lua seeds `vararg.lua`, `sort.lua`, `pm.lua` timed out when routed to some `harness_base_*` candidates.
