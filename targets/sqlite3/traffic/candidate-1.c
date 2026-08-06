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
    TF_String const4 = traffic_const_string(fdp);
    traffic_assert(true);
    sqlite3_stmt* out7_slot; sqlite3_stmt** out7 = &out7_slot; 
    char** null10 = NULL;
    int var19 = sqlite3_prepare_v2((*out0), const4, all_sql, out7, null10);
    traffic_assert(true);
    traffic_assert(true);
  } else if (!((var2 == 0))) {
  }
}