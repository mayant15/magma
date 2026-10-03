#include <traffic.h>

#include <sqlite3.h>

int fuzz_2(char* data, int size) {
  sqlite3_stmt* null25 = NULL;
  int var28 = sqlite3_step(null25);
  traffic_assert(true);
  sqlite3_stmt* null53 = NULL;
  int var58 = sqlite3_finalize(null53);
  traffic_assert(true);
  int var88 = sqlite3_reset(null25);
  traffic_assert(true);
}