#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_0(uint8_t* data, int size) {
  char* var35 = sf_error_number(size);
  traffic_assert(true);
  SF_CHUNK_ITERATOR* null69 = NULL;
  SF_CHUNK_INFO out70_slot; SF_CHUNK_INFO* out70 = &out70_slot;
  int var72 = sf_get_chunk_size(null69, out70);
  traffic_assert(true);
  traffic_assert(true);
  char* var110 = sf_version_string();
}