#include <traffic.h>

#include <sqlite3.h>

int fuzz_1(char* data, int size) {
  sqlite3* null7 = NULL;
  int const10 = -1;
  int var28 = sqlite3_limit(null7, size, const10);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const32 = "*cm&FUDBABKb%";
  sqlite3* out34_slot; sqlite3** out34 = &out34_slot;
  int var60 = sqlite3_open(const32, out34);
  traffic_assert(true);
  traffic_assert(true);
}