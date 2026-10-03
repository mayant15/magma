#include <traffic.h>

#include <sqlite3.h>

int fuzz_2(char* data, int size) {
  TF_String const0 = "u][eVC";
  sqlite3* out2_slot; sqlite3** out2 = &out2_slot;
  int var28 = sqlite3_open(const0, out2);
  traffic_assert(true);
  traffic_assert(true);
  sqlite3* null36 = NULL;
  int var59 = sqlite3_close(null36);
  traffic_assert(true);
  int const77 = -1;
  sqlite3_stmt* out79_slot; sqlite3_stmt** out79 = &out79_slot;
  char* out81_slot; char** out81 = &out81_slot;
  int var89 = sqlite3_prepare_v2(null36, data, const77, out79, out81);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}