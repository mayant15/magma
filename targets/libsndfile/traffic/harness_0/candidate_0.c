#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_0(uint8_t* data, int size) {
  char* var25 = sf_version_string();
  SF_INFO out46_slot; SF_INFO* out46 = &out46_slot;
  int var55 = sf_format_check(out46);
  SndFileP out60_slot; SndFileP* out60 = &out60_slot;
  VIO_DATA out61_slot; VIO_DATA* out61 = &out61_slot;
  SF_VIRTUAL_IO out62_slot; SF_VIRTUAL_IO* out62 = &out62_slot;
  SF_INFO out63_slot; SF_INFO* out63 = &out63_slot;
  int var85 = sf_init_file(data, size, out60, out61, out62, out63);
  if (!((var85 == 0))) {
    traffic_assert(true);
    int var114 = sf_error((*out60));
    traffic_assert(true);
    traffic_assert(true);
  } else if ((var85 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    if (!((out63 == NULL))) {
      int var157 = sf_format_check(out63);
      int var199 = sf_error((*out60));
      traffic_assert(true);
      traffic_assert(true);
      char* var242 = sf_strerror((*out60));
      traffic_assert(true);
      int var285 = sf_fuzz_readf_int((*out60), var199);
      traffic_assert(true);
      int var328 = sf_fuzz_readf_double((*out60), var285);
      traffic_assert(true);
      int const361 = 1;
      int var371 = sf_seek((*out60), var328, const361);
      traffic_assert(true);
      int const402 = -1;
      int const404 = 1;
      int var414 = sf_seek((*out60), const402, const404);
      traffic_assert(true);
      SF_CHUNK_INFO* null451 = NULL;
      SF_CHUNK_ITERATOR* var457 = sf_get_chunk_iterator((*out60), null451);
    } else {
    }
  }
}