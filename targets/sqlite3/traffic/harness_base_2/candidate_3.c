#include <traffic.h>

#include <sqlite3.h>

int fuzz_3(char* data, int size) {
  sqlite3_stmt* null25 = NULL;
  int var28 = sqlite3_step(null25);
  traffic_assert(true);
  sqlite3* null37 = NULL;
  int const40 = 0;
  int var58 = sqlite3_limit(null37, size, const40);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}