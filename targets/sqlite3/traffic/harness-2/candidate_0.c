#include <traffic.h>

#include <sqlite3.h>

int fuzz_0(char* data, int size) {
  TF_String const0 = ":memory:";
  sqlite3* out2_slot; sqlite3** out2 = &out2_slot;
  int var9 = sqlite3_open(const0, out2);
  traffic_assert(true);
  if ((var9 == 0)) {
    traffic_assert(true);
    sqlite3_stmt* out38_slot; sqlite3_stmt** out38 = &out38_slot;
    char* out39_slot; char** out39 = &out39_slot;
    int var44 = sqlite3_prepare_v2((*out2), data, size, out38, out39);
  } else if (!((var9 == 0))) {
    traffic_assert(true);
    int var23 = sqlite3_close((*out2));
  }
}