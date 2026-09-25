#include <traffic.h>

#include <sqlite3.h>

int fuzz_3(char* data, int size) {
  sqlite3* null13 = NULL;
  char* null15 = NULL;
  sqlite3_stmt* out18_slot; sqlite3_stmt** out18 = &out18_slot;
  char* out20_slot; char** out20 = &out20_slot;
  int var28 = sqlite3_prepare_v2(null13, null15, size, out18, out20);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}