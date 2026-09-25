#include <traffic.h>

#include <sqlite3.h>

int fuzz_1(char* data, int size) {
  TF_String const0 = ":memory:";
  sqlite3* out2_slot; sqlite3** out2 = &out2_slot;
  int var9 = sqlite3_open(const0, out2);
  traffic_assert(true);
  if ((var9 == 0)) {
    traffic_assert(true);
    sqlite3_stmt* out27_slot; sqlite3_stmt** out27 = &out27_slot;
    char* out28_slot; char** out28 = &out28_slot;
    int var33 = sqlite3_prepare_v2((*out2), data, size, out27, out28);
    TF_String const34 = ":memory:";
    sqlite3* out36_slot; sqlite3** out36 = &out36_slot;
    int var43 = sqlite3_open(const34, out36);
    traffic_assert(true);
  } else if (!((var9 == 0))) {
    traffic_assert(true);
  }
}