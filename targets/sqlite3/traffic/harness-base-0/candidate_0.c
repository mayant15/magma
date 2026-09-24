#include <traffic.h>

#include <sqlite3.h>

int fuzz_0(char* data, int size) {
  sqlite3* null13 = NULL;
  char out14_slot; char* out14 = &out14_slot;
  int const16 = 1;
  sqlite3_stmt* out18_slot; sqlite3_stmt** out18 = &out18_slot;
  char* out20_slot; char** out20 = &out20_slot;
  int var28 = sqlite3_prepare_v2(null13, out14, const16, out18, out20);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const34 = "mYg(mpFf#Y6vz6WD";
  sqlite3* out36_slot; sqlite3** out36 = &out36_slot;
  int var62 = sqlite3_open(const34, out36);
  traffic_assert(true);
  traffic_assert(true);
}