# Prefix distribution: traffic harnesses (AFL++, 5 min x 2 repeats)

Per-campaign data: `prefix-dist.csv`. `candidate_counts` = executions dispatched to each `case` (`index % NUM_CANDIDATES`, `index` = first 4 bytes, little-endian). All seeds start with `00 00 00 00`.

| lib | harnesses | campaigns | executions | non-zero prefix | candidates hit | top-candidate share (mean) |
|---|---|---:|---:|---:|---:|---:|
| libpng | harness_N | 6 | 3,130,223 | 99.5% | 12/12 | 93% |
| libpng | harness_base_N | 6 | 3,531,182 | 97.9% | 20/20 | 57% |
| libsndfile | harness_N | 6 | 2,158,327 | 69.8% | 60/60 | 48% |
| libsndfile | harness_base_N | 6 | 2,654,100 | 81.4% | 16/16 | 71% |
| libtiff | harness_N | 6 | 2,500,696 | 59.3% | 18/18 | 86% |
| libtiff | harness_base_N | 6 | 3,039,077 | 71.3% | 28/28 | 51% |
| libxml2 | harness_N | 6 | 2,495,941 | 94.8% | 64/64 | 48% |
| libxml2 | harness_base_N | 6 | 3,356,133 | 86.2% | 82/82 | 23% |
| lua | harness_N | 6 | 2,820,281 | 89.6% | 44/44 | 77% |
| lua | harness_base_N | 6 | 2,692,617 | 92.7% | 56/56 | 61% |
| openssl | harness_N | 6 | 1,106,607 | 85.2% | 18/18 | 61% |
| openssl | harness_base_N | 6 | 1,246,095 | 85.7% | 42/42 | 47% |
| sqlite3 | harness_N | 6 | 2,036,829 | 94.8% | 26/26 | 62% |
| sqlite3 | harness_base_N | 6 | 2,907,322 | 93.6% | 20/20 | 48% |

Notes: counts are cumulative over each 5-minute campaign (including seed import). `candidates hit` sums over campaigns (every candidate got executions in every campaign). `harness_N` = `harness_[0-2]`, `harness_base_N` = `harness_base_[0-2]`. `prefix-dist-run1-partial.csv` is an aborted ~9 min libxml2 run kept for reference.
