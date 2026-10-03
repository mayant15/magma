#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_8(uint8_t* data, int size) {
  SndFileP out4_slot; SndFileP* out4 = &out4_slot;
  VIO_DATA out5_slot; VIO_DATA* out5 = &out5_slot;
  SF_VIRTUAL_IO out6_slot; SF_VIRTUAL_IO* out6 = &out6_slot;
  SF_INFO out7_slot; SF_INFO* out7 = &out7_slot;
  int var29 = sf_init_file(data, size, out4, out5, out6, out7);
  if (!((var29 == 0))) {
    traffic_assert(true);
    SF_INFO out91_slot; SF_INFO* out91 = &out91_slot;
    int var100 = sf_format_check(out91);
    if ((var100 == 1)) {
      traffic_assert(true);
    } else if (!((var100 == 1))) {
      traffic_assert(true);
    }
  } else if ((var29 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    TF_String const50 = "S[dDRvfNOjn1hJ&p6yv";
    SF_CHUNK_ITERATOR* var74 = sf_fuzz_get_chunk_iterator((*out4), const50);
    if (!((var74 == NULL))) {
      traffic_assert(true);
      traffic_assert(true);
    } else if ((var74 == NULL)) {
      traffic_assert(true);
      SF_CHUNK_INFO* null141 = NULL;
      SF_CHUNK_ITERATOR* var147 = sf_get_chunk_iterator((*out4), null141);
      if (!((var147 == NULL))) {
        traffic_assert(true);
        traffic_assert(true);
        int var235 = sf_error((*out4));
        traffic_assert(true);
        traffic_assert(true);
        int var278 = sf_fuzz_readf_double((*out4), var235);
        traffic_assert(true);
        SF_CHUNK_ITERATOR* var364 = sf_next_chunk_iterator(var147);
      } else if ((var147 == NULL)) {
        traffic_assert(true);
        int const162 = -1;
        int var192 = sf_fuzz_readf_double((*out4), const162);
        traffic_assert(true);
        char* var321 = sf_strerror((*out4));
        traffic_assert(true);
        int var406 = sf_fuzz_writef_double((*out4), var192);
        traffic_assert(true);
      }
    }
  }
}