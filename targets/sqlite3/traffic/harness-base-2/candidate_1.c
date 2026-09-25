#include <traffic.h>

#include <sqlite3.h>

int fuzz_1(char* data, int size) {
  sqlite3_stmt* null25 = NULL;
  int var28 = sqlite3_step(null25);
  traffic_assert(true);
  sqlite3* null35 = NULL;
  int var58 = sqlite3_close(null35);
  traffic_assert(true);
  int var88 = sqlite3_finalize(null25);
  traffic_assert(true);
}