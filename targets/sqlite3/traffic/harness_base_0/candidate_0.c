#include <traffic.h>

#include <sqlite3.h>

int fuzz_0(char* data, int size) {
  sqlite3* null7 = NULL;
  int const10 = -1;
  int var28 = sqlite3_limit(null7, size, const10);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var60 = sqlite3_close(null7);
  traffic_assert(true);
  sqlite3_stmt* null89 = NULL;
  int var90 = sqlite3_reset(null89);
  traffic_assert(true);
}