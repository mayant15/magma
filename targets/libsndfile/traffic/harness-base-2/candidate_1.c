#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  SF_CHUNK_ITERATOR* null18 = NULL;
  int var35 = sf_fuzz_get_chunk_data(null18);
  traffic_assert(true);
  SF_CHUNK_ITERATOR* null67 = NULL;
  SF_CHUNK_ITERATOR* var72 = sf_next_chunk_iterator(null67);
  traffic_assert(true);
  SF_INFO out98_slot; SF_INFO* out98 = &out98_slot;
  int var109 = sf_format_check(out98);
  traffic_assert(true);
  uint8_t out111_slot; uint8_t* out111 = &out111_slot;
  int const113 = 0;
  SndFileP out115_slot; SndFileP* out115 = &out115_slot;
  VIO_DATA out117_slot; VIO_DATA* out117 = &out117_slot;
  SF_VIRTUAL_IO out119_slot; SF_VIRTUAL_IO* out119 = &out119_slot;
  int var146 = sf_init_file(out111, const113, out115, out117, out119, out98);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}