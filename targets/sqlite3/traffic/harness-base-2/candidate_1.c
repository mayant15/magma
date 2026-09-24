#include <traffic.h>

#include <sqlite3.h>

int fuzz_1(char* data, int size) {
  sqlite3_stmt* null25 = NULL;
  int var28 = sqlite3_step(null25);
  traffic_assert(true);
  int var58 = sqlite3_finalize(null25);
  traffic_assert(true);
  sqlite3_stmt* null87 = NULL;
  int var88 = sqlite3_reset(null87);
  traffic_assert(true);
  sqlite3* null103 = NULL;
  char out104_slot; char* out104 = &out104_slot;
  sqlite3_stmt* out108_slot; sqlite3_stmt** out108 = &out108_slot;
  char** null111 = NULL;
  int var118 = sqlite3_prepare_v2(null103, out104, var58, out108, null111);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var152 = sqlite3_limit(null103, size, var88);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}