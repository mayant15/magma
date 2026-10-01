#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  char* var35 = sf_version_string();
  SF_CHUNK_ITERATOR* null68 = NULL;
  SF_CHUNK_INFO out69_slot; SF_CHUNK_INFO* out69 = &out69_slot;
  int var71 = sf_get_chunk_size(null68, out69);
  traffic_assert(true);
  traffic_assert(true);
  SF_CHUNK_ITERATOR* null104 = NULL;
  SF_CHUNK_ITERATOR* var109 = sf_next_chunk_iterator(null104);
  traffic_assert(true);
  SF_INFO out135_slot; SF_INFO* out135 = &out135_slot;
  int var146 = sf_format_check(out135);
  traffic_assert(true);
  uint8_t out148_slot; uint8_t* out148 = &out148_slot;
  SndFileP out152_slot; SndFileP* out152 = &out152_slot;
  VIO_DATA out154_slot; VIO_DATA* out154 = &out154_slot;
  SF_VIRTUAL_IO out156_slot; SF_VIRTUAL_IO* out156 = &out156_slot;
  int var183 = sf_init_file(out148, var71, out152, out154, out156, out135);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}