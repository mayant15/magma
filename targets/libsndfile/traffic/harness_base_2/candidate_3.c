#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_3(uint8_t* data, int size) {
  SF_CHUNK_ITERATOR* null18 = NULL;
  int var35 = sf_fuzz_get_chunk_data(null18);
  traffic_assert(true);
  char* var72 = sf_version_string();
  SndFileP out77_slot; SndFileP* out77 = &out77_slot;
  VIO_DATA out79_slot; VIO_DATA* out79 = &out79_slot;
  SF_VIRTUAL_IO out81_slot; SF_VIRTUAL_IO* out81 = &out81_slot;
  SF_INFO out83_slot; SF_INFO* out83 = &out83_slot;
  int var108 = sf_init_file(data, size, out77, out79, out81, out83);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var150 = sf_format_check(out83);
  traffic_assert(true);
}