#include <traffic.h>

#include <sqlite3.h>

int fuzz_0(char* data, int size) {
  TF_String const0 = ":memory:";
  sqlite3* out2_slot; sqlite3** out2 = &out2_slot;
  int var9 = sqlite3_open(const0, out2);
  traffic_assert(true);
  if ((var9 == 0)) {
    traffic_assert(true);
    int var44 = sqlite3_close((*out2));
  } else if (!((var9 == 0))) {
    traffic_assert(true);
    int var23 = sqlite3_close((*out2));
  }
}