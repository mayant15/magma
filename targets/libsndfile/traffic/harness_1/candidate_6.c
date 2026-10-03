#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_6(uint8_t* data, int size) {
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
  } else if ((var29 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    int const68 = 0;
    int var101 = sf_fuzz_writef_int((*out4), const68);
    traffic_assert(true);
    int var144 = sf_current_byterate((*out4));
    traffic_assert(true);
    int const175 = -1;
    if (((var101 == 0) || ((var101 == 1) || (var101 == 2)))) {
      int var187 = sf_seek((*out4), const175, var101);
      traffic_assert(true);
      int const203 = -1;
      int var230 = sf_fuzz_writef_double((*out4), const203);
      traffic_assert(true);
      int const263 = 1;
      int var273 = sf_seek((*out4), var144, const263);
      traffic_assert(true);
    } else {
    }
  }
}