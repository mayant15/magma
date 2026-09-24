#include <traffic.h>

#include <sqlite3.h>

int fuzz_0(char* data, int size) {
  TF_String const0 = ":memory:";
  sqlite3* out2_slot; sqlite3** out2 = &out2_slot;
  int var9 = sqlite3_open(const0, out2);
  traffic_assert(true);
  if ((var9 == 0)) {
    traffic_assert(true);
    sqlite3_stmt* out26_slot; sqlite3_stmt** out26 = &out26_slot;
    char* out27_slot; char** out27 = &out27_slot;
    int var32 = sqlite3_prepare_v2((*out2), data, size, out26, out27);
  } else if (!((var9 == 0))) {
  }
}