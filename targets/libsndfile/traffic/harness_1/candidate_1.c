#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  SndFileP out4_slot; SndFileP* out4 = &out4_slot;
  VIO_DATA out5_slot; VIO_DATA* out5 = &out5_slot;
  SF_VIRTUAL_IO out6_slot; SF_VIRTUAL_IO* out6 = &out6_slot;
  SF_INFO out7_slot; SF_INFO* out7 = &out7_slot;
  int var29 = sf_init_file(data, size, out4, out5, out6, out7);
  if (!((var29 == 0))) {
    traffic_assert(true);
    SF_INFO out91_slot; SF_INFO* out91 = &out91_slot;
    int var100 = sf_format_check(out91);
    char* var126 = sf_strerror((*out4));
    traffic_assert(true);
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
      int const136 = 0;
      int var172 = sf_fuzz_readf_int((*out4), const136);
      traffic_assert(true);
    }
  }
}