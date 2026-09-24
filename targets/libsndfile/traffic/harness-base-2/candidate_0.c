#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_0(uint8_t* data, int size) {
  int const21 = -1;
  char* var35 = sf_error_number(const21);
  traffic_assert(true);
  char* var72 = sf_error_number(size);
  traffic_assert(true);
  SF_CHUNK_ITERATOR* null92 = NULL;
  int var109 = sf_fuzz_get_chunk_data(null92);
  traffic_assert(true);
  char* var146 = sf_version_string();
  SF_CHUNK_ITERATOR* var182 = sf_next_chunk_iterator(null92);
  traffic_assert(true);
  SndFileP out188_slot; SndFileP* out188 = &out188_slot;
  VIO_DATA out190_slot; VIO_DATA* out190 = &out190_slot;
  SF_VIRTUAL_IO out192_slot; SF_VIRTUAL_IO* out192 = &out192_slot;
  SF_INFO out194_slot; SF_INFO* out194 = &out194_slot;
  int var219 = sf_init_file(data, var109, out188, out190, out192, out194);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const228 = 1;
  int var261 = sf_init_file(data, const228, out188, out190, out192, out194);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}