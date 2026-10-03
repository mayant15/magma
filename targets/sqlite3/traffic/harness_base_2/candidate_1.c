#include <traffic.h>

#include <sqlite3.h>

int fuzz_1(char* data, int size) {
  sqlite3_stmt* null25 = NULL;
  int var28 = sqlite3_step(null25);
  traffic_assert(true);
  sqlite3* null43 = NULL;
  int const46 = 1;
  sqlite3_stmt* out48_slot; sqlite3_stmt** out48 = &out48_slot;
  char* out50_slot; char** out50 = &out50_slot;
  int var58 = sqlite3_prepare_v2(null43, data, const46, out48, out50);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}