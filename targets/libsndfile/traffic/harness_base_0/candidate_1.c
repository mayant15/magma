#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  char* var35 = sf_error_number(size);
  traffic_assert(true);
  SF_CHUNK_ITERATOR* null67 = NULL;
  SF_CHUNK_ITERATOR* var72 = sf_next_chunk_iterator(null67);
  traffic_assert(true);
}