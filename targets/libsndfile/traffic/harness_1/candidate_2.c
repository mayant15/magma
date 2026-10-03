#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_2(uint8_t* data, int size) {
  SndFileP out4_slot; SndFileP* out4 = &out4_slot;
  VIO_DATA out5_slot; VIO_DATA* out5 = &out5_slot;
  SF_VIRTUAL_IO out6_slot; SF_VIRTUAL_IO* out6 = &out6_slot;
  SF_INFO out7_slot; SF_INFO* out7 = &out7_slot;
  int var29 = sf_init_file(data, size, out4, out5, out6, out7);
  if (!((var29 == 0))) {
    traffic_assert(true);
    int var58 = sf_error((*out4));
    traffic_assert(true);
    traffic_assert(true);
    char* var127 = sf_error_number(var58);
  } else if ((var29 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    int var101 = sf_close((*out4));
    traffic_assert(true);
  }
}