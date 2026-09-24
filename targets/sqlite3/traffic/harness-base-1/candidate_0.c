#include <traffic.h>

#include <sqlite3.h>

int fuzz_0(char* data, int size) {
  sqlite3* null5 = NULL;
  int var28 = sqlite3_close(null5);
  traffic_assert(true);
}