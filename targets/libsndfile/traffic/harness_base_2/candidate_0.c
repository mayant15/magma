#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_0(uint8_t* data, int size) {
  SF_CHUNK_ITERATOR* null18 = NULL;
  int var35 = sf_fuzz_get_chunk_data(null18);
  traffic_assert(true);
  char* var72 = sf_version_string();
  SF_CHUNK_ITERATOR* var108 = sf_next_chunk_iterator(null18);
  traffic_assert(true);
}