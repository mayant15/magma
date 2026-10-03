#include <traffic.h>

#include <sqlite3.h>

int fuzz_1(char* data, int size) {
  TF_String const0 = "u][eVC";
  sqlite3* out2_slot; sqlite3** out2 = &out2_slot;
  int var28 = sqlite3_open(const0, out2);
  traffic_assert(true);
  traffic_assert(true);
  sqlite3_stmt* null54 = NULL;
  int var59 = sqlite3_finalize(null54);
  traffic_assert(true);
  sqlite3* null68 = NULL;
  int var89 = sqlite3_limit(null68, size, var28);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}