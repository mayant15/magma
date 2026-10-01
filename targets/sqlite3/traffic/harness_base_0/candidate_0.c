#include <traffic.h>

#include <sqlite3.h>

int fuzz_0(char* data, int size) {
  sqlite3_stmt* null27 = NULL;
  int var28 = sqlite3_reset(null27);
  traffic_assert(true);
  sqlite3* null37 = NULL;
  int const40 = -1;
  int var58 = sqlite3_limit(null37, size, const40);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}