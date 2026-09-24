#include <traffic.h>

#include <sqlite3.h>

int fuzz_1(char* data, int size) {
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
  sqlite3_stmt* null57 = NULL;
  int var62 = sqlite3_finalize(null57);
  traffic_assert(true);
  sqlite3_stmt* null89 = NULL;
  int var92 = sqlite3_step(null89);
  traffic_assert(true);
  int var122 = sqlite3_close(null13);
  traffic_assert(true);
  int const132 = -1;
  int const134 = 1;
  int var152 = sqlite3_limit(null13, const132, const134);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var184 = sqlite3_reset(null57);
  traffic_assert(true);
}