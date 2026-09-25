#include <traffic.h>

#include <sqlite3.h>

int fuzz_3(char* data, int size) {
  sqlite3_stmt* null25 = NULL;
  int var28 = sqlite3_step(null25);
  traffic_assert(true);
}