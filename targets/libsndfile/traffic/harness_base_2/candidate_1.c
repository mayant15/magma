#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  SF_CHUNK_ITERATOR* null18 = NULL;
  int var35 = sf_fuzz_get_chunk_data(null18);
  traffic_assert(true);
  char* var72 = sf_error_number(size);
  traffic_assert(true);
}