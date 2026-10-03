#include <traffic.h>

#include <sqlite3.h>

int fuzz_2(char* data, int size) {
  sqlite3* null7 = NULL;
  int const10 = -1;
  int var28 = sqlite3_limit(null7, size, const10);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  sqlite3_stmt* out50_slot; sqlite3_stmt** out50 = &out50_slot;
  char** null53 = NULL;
  int var60 = sqlite3_prepare_v2(null7, data, var28, out50, null53);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  sqlite3_stmt* null91 = NULL;
  int var94 = sqlite3_step(null91);
  traffic_assert(true);
  int var124 = sqlite3_finalize(null91);
  traffic_assert(true);
}