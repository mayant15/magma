#include <traffic.h>

#include <sqlite3.h>

int fuzz_2(char* data, int size) {
  sqlite3* null5 = NULL;
  int var28 = sqlite3_close(null5);
  traffic_assert(true);
  sqlite3_stmt* null53 = NULL;
  int var58 = sqlite3_finalize(null53);
  traffic_assert(true);
  int var88 = sqlite3_reset(null53);
  traffic_assert(true);
  int var118 = sqlite3_limit(null5, size, var88);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}