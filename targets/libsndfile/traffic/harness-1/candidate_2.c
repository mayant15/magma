#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_2(uint8_t* data, int size) {
  SndFileP out4_slot; SndFileP* out4 = &out4_slot;
  VIO_DATA out5_slot; VIO_DATA* out5 = &out5_slot;
  SF_VIRTUAL_IO out6_slot; SF_VIRTUAL_IO* out6 = &out6_slot;
  SF_INFO out7_slot; SF_INFO* out7 = &out7_slot;
  int var29 = sf_init_file(data, size, out4, out5, out6, out7);
  SF_INFO out46_slot; SF_INFO* out46 = &out46_slot;
  int var55 = sf_format_check(out46);
  if (!((var29 == 0))) {
    traffic_assert(true);
    char* var84 = sf_strerror((*out4));
    traffic_assert(true);
  } else if ((var29 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    int const97 = 0;
    int var127 = sf_fuzz_readf_double((*out4), const97);
    traffic_assert(true);
    int var170 = sf_fuzz_writef_int((*out4), var127);
    traffic_assert(true);
    int const180 = 1;
    int var213 = sf_fuzz_writef_int((*out4), const180);
    traffic_assert(true);
    char* var256 = sf_strerror((*out4));
    traffic_assert(true);
    int var299 = sf_fuzz_writef_double((*out4), var213);
    traffic_assert(true);
    int const332 = 0;
    int var342 = sf_seek((*out4), var170, const332);
    traffic_assert(true);
    int const349 = -1;
    int var385 = sf_fuzz_readf_int((*out4), const349);
    traffic_assert(true);
    TF_String const404 = "VUZh977)VHWb&SPMp)0";
    SF_CHUNK_ITERATOR* var428 = sf_fuzz_get_chunk_iterator((*out4), const404);
    if (!((out7 == NULL))) {
      int var454 = sf_format_check(out7);
    } else {
    }
  }
}