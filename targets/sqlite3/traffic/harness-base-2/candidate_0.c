#include <traffic.h>

#include <sqlite3.h>

int fuzz_0(char* data, int size) {
  sqlite3_stmt* null25 = NULL;
  int var28 = sqlite3_step(null25);
  traffic_assert(true);
  int var58 = sqlite3_finalize(null25);
  traffic_assert(true);
  sqlite3* null65 = NULL;
  int var88 = sqlite3_close(null65);
  traffic_assert(true);
  TF_String const90 = "&8WZpkNfcG@zbsSbu";
  sqlite3* out92_slot; sqlite3** out92 = &out92_slot;
  int var118 = sqlite3_open(const90, out92);
  traffic_assert(true);
  traffic_assert(true);
}