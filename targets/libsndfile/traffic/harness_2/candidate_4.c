#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_4(uint8_t* data, int size) {
  char* var25 = sf_version_string();
  SndFileP out30_slot; SndFileP* out30 = &out30_slot;
  VIO_DATA out31_slot; VIO_DATA* out31 = &out31_slot;
  SF_VIRTUAL_IO out32_slot; SF_VIRTUAL_IO* out32 = &out32_slot;
  SF_INFO out33_slot; SF_INFO* out33 = &out33_slot;
  int var55 = sf_init_file(data, size, out30, out31, out32, out33);
  if (!((var55 == 0))) {
    traffic_assert(true);
  } else if ((var55 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    char* var100 = sf_strerror((*out30));
    traffic_assert(true);
    int const110 = 1;
    int var143 = sf_fuzz_writef_int((*out30), const110);
    traffic_assert(true);
  }
}