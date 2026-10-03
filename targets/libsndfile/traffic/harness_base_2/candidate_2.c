#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_2(uint8_t* data, int size) {
  SF_CHUNK_ITERATOR* null18 = NULL;
  int var35 = sf_fuzz_get_chunk_data(null18);
  traffic_assert(true);
  char* var72 = sf_version_string();
  int const94 = 1;
  char* var108 = sf_error_number(const94);
  traffic_assert(true);
}