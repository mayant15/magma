#include <traffic.h>

#include <sqlite3.h>

int fuzz_0(char* data, int size) {
  sqlite3_stmt* null25 = NULL;
  int var28 = sqlite3_step(null25);
  traffic_assert(true);
  int var58 = sqlite3_reset(null25);
  traffic_assert(true);
  TF_String const60 = "MD)[AAt@q#9raeL*w";
  sqlite3* out62_slot; sqlite3** out62 = &out62_slot;
  int var88 = sqlite3_open(const60, out62);
  traffic_assert(true);
  traffic_assert(true);
  sqlite3* null98 = NULL;
  int var119 = sqlite3_limit(null98, var28, var58);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  sqlite3* null136 = NULL;
  int const139 = 1;
  sqlite3_stmt* out141_slot; sqlite3_stmt** out141 = &out141_slot;
  char* out143_slot; char** out143 = &out143_slot;
  int var151 = sqlite3_prepare_v2(null136, data, const139, out141, out143);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}