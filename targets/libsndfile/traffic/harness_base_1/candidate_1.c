#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  SF_CHUNK_ITERATOR* null18 = NULL;
  int var35 = sf_fuzz_get_chunk_data(null18);
  traffic_assert(true);
  SF_INFO out61_slot; SF_INFO* out61 = &out61_slot;
  int var72 = sf_format_check(out61);
  traffic_assert(true);
  char* var109 = sf_error_number(var72);
  traffic_assert(true);
  char* var146 = sf_error_number(size);
  traffic_assert(true);
  int const169 = 1;
  char* var183 = sf_error_number(const169);
  traffic_assert(true);
  SndFileP out189_slot; SndFileP* out189 = &out189_slot;
  VIO_DATA out191_slot; VIO_DATA* out191 = &out191_slot;
  SF_VIRTUAL_IO out193_slot; SF_VIRTUAL_IO* out193 = &out193_slot;
  int var220 = sf_init_file(data, const169, out189, out191, out193, out61);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}