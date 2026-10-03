#include <traffic.h>

#include <sqlite3.h>

int fuzz_1(char* data, int size) {
  TF_String const0 = ":memory:";
  sqlite3* out2_slot; sqlite3** out2 = &out2_slot;
  int var9 = sqlite3_open(const0, out2);
  traffic_assert(true);
  if ((var9 == 0)) {
    traffic_assert(true);
    int const19 = 0;
    int var33 = sqlite3_limit((*out2), const19, size);
    traffic_assert(true);
  } else if (!((var9 == 0))) {
    traffic_assert(true);
  }
}