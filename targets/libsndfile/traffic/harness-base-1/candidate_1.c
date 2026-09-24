#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  SF_CHUNK_ITERATOR* null30 = NULL;
  SF_CHUNK_ITERATOR* var35 = sf_next_chunk_iterator(null30);
  traffic_assert(true);
  SF_CHUNK_ITERATOR* null69 = NULL;
  SF_CHUNK_INFO out70_slot; SF_CHUNK_INFO* out70 = &out70_slot;
  int var72 = sf_get_chunk_size(null69, out70);
  traffic_assert(true);
  traffic_assert(true);
  SF_INFO out99_slot; SF_INFO* out99 = &out99_slot;
  int var110 = sf_format_check(out99);
  traffic_assert(true);
}