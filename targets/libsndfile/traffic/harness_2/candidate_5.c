#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_5(uint8_t* data, int size) {
  char* var25 = sf_version_string();
  SndFileP out30_slot; SndFileP* out30 = &out30_slot;
  VIO_DATA out31_slot; VIO_DATA* out31 = &out31_slot;
  SF_VIRTUAL_IO out32_slot; SF_VIRTUAL_IO* out32 = &out32_slot;
  SF_INFO out33_slot; SF_INFO* out33 = &out33_slot;
  int var55 = sf_init_file(data, size, out30, out31, out32, out33);
  if (!((var55 == 0))) {
    traffic_assert(true);
    SF_INFO out75_slot; SF_INFO* out75 = &out75_slot;
    int var84 = sf_format_check(out75);
  } else if ((var55 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    int const90 = -1;
    int var126 = sf_fuzz_readf_int((*out30), const90);
    traffic_assert(true);
    int var169 = sf_fuzz_readf_double((*out30), var126);
    traffic_assert(true);
    int const200 = 1;
    if (((var169 == 0) || ((var169 == 1) || (var169 == 2)))) {
      int var212 = sf_seek((*out30), const200, var169);
      traffic_assert(true);
      int const225 = 1;
      int var255 = sf_fuzz_readf_double((*out30), const225);
      traffic_assert(true);
    } else {
    }
  }
}