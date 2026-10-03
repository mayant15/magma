#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_6(uint8_t* data, int size) {
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
    if ((var84 == 1)) {
      traffic_assert(true);
    } else if (!((var84 == 1))) {
      traffic_assert(true);
    }
  } else if ((var55 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    int const114 = 0;
    int const116 = 1;
    int var126 = sf_seek((*out30), const114, const116);
    traffic_assert(true);
    int var171 = sf_current_byterate((*out30));
    traffic_assert(true);
    int const202 = -1;
    int const204 = 1;
    int var214 = sf_seek((*out30), const202, const204);
    traffic_assert(true);
    if (((var126 == 0) || ((var126 == 1) || (var126 == 2)))) {
      int var257 = sf_seek((*out30), var171, var126);
      traffic_assert(true);
    } else {
    }
  }
}