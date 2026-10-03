#include <traffic.h>

#include <sqlite3.h>

int fuzz_4(char* data, int size) {
  TF_String const0 = ":memory:";
  sqlite3* out2_slot; sqlite3** out2 = &out2_slot;
  int var9 = sqlite3_open(const0, out2);
  traffic_assert(true);
  if ((var9 == 0)) {
    traffic_assert(true);
    sqlite3_stmt* out27_slot; sqlite3_stmt** out27 = &out27_slot;
    char* out28_slot; char** out28 = &out28_slot;
    int var33 = sqlite3_prepare_v2((*out2), data, size, out27, out28);
    if ((var33 == 0)) {
      traffic_assert(true);
      traffic_assert(true);
      traffic_assert(true);
      int var72 = sqlite3_step((*out27));
      if ((var72 == 0)) {
        traffic_assert(true);
      } else if ((var72 == 5)) {
        traffic_assert(true);
      } else if ((var72 == 101)) {
        traffic_assert(true);
        int var95 = sqlite3_finalize((*out27));
        traffic_assert(true);
        int var112 = sqlite3_close((*out2));
      } else if ((var72 == 100)) {
        traffic_assert(true);
      } else if ((var72 == 21)) {
        traffic_assert(true);
      } else if (true) {
        traffic_assert(true);
      }
    } else if (!((var33 == 0))) {
      traffic_assert(true);
      traffic_assert(true);
      int const45 = 0;
      int const47 = 0;
      int var54 = sqlite3_limit((*out2), const45, const47);
      traffic_assert(true);
    }
  } else if (!((var9 == 0))) {
    traffic_assert(true);
  }
}