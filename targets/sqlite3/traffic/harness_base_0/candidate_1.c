#include <traffic.h>

#include <sqlite3.h>

int fuzz_1(char* data, int size) {
  TF_String const0 = "h]ErvZzF&5Dp(aUKP";
  sqlite3* out2_slot; sqlite3** out2 = &out2_slot;
  int var28 = sqlite3_open(const0, out2);
  traffic_assert(true);
  traffic_assert(true);
  sqlite3_stmt* null56 = NULL;
  int var59 = sqlite3_step(null56);
  traffic_assert(true);
}