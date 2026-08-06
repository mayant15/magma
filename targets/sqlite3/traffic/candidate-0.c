#include <traffic.h>

#include <sqlite3.h>

int LLVMFuzzerTestOneInput(uint8_t* data, int size) {
  FuzzedDataProvider* fdp = traffic_provider_init(data, size);
  TF_String name = ":memory:";
  int all_sql = -1;
  sqlite3* out0_slot; sqlite3** out0 = &out0_slot; 
  int var2 = sqlite3_open(name, out0);
  if ((var2 == 0)) {
    traffic_assert(true);
    int var19 = sqlite3_changes((*out0));
    traffic_assert((0 <= var19));
    traffic_assert(true);
    int var39 = sqlite3_close((*out0));
  } else if (!((var2 == 0))) {
  }
}