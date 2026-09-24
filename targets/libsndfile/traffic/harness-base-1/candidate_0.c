#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_0(uint8_t* data, int size) {
  SF_CHUNK_ITERATOR* null30 = NULL;
  SF_CHUNK_ITERATOR* var35 = sf_next_chunk_iterator(null30);
  traffic_assert(true);
  char* var72 = sf_version_string();
}