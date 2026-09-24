#include <traffic.h>

#include <sqlite3.h>

int fuzz_1(char* data, int size) {
  sqlite3_stmt* null27 = NULL;
  int var28 = sqlite3_reset(null27);
  traffic_assert(true);
  int var58 = sqlite3_step(null27);
  traffic_assert(true);
  sqlite3_stmt* null83 = NULL;
  int var88 = sqlite3_finalize(null83);
  traffic_assert(true);
  TF_String const90 = "pLMKO6^qIIwtWDs";
  sqlite3* out92_slot; sqlite3** out92 = &out92_slot;
  int var118 = sqlite3_open(const90, out92);
  traffic_assert(true);
  traffic_assert(true);
  sqlite3* null128 = NULL;
  int const131 = 0;
  int var149 = sqlite3_limit(null128, var58, const131);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  sqlite3_stmt* out171_slot; sqlite3_stmt** out171 = &out171_slot;
  char** null174 = NULL;
  int var181 = sqlite3_prepare_v2(null128, data, var118, out171, null174);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}