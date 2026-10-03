#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_2(uint8_t* data, int size) {
  SF_INFO out16_slot; SF_INFO* out16 = &out16_slot;
  int var25 = sf_format_check(out16);
  if ((var25 == 1)) {
    traffic_assert(true);
    SndFileP out65_slot; SndFileP* out65 = &out65_slot;
    VIO_DATA out66_slot; VIO_DATA* out66 = &out66_slot;
    SF_VIRTUAL_IO out67_slot; SF_VIRTUAL_IO* out67 = &out67_slot;
    SF_INFO out68_slot; SF_INFO* out68 = &out68_slot;
    int var90 = sf_init_file(data, size, out65, out66, out67, out68);
  } else if (!((var25 == 1))) {
    traffic_assert(true);
    SndFileP out32_slot; SndFileP* out32 = &out32_slot;
    VIO_DATA out33_slot; VIO_DATA* out33 = &out33_slot;
    SF_VIRTUAL_IO out34_slot; SF_VIRTUAL_IO* out34 = &out34_slot;
    if (!((out16 == NULL))) {
      int var57 = sf_init_file(data, size, out32, out33, out34, out16);
      if (!((var57 == 0))) {
        traffic_assert(true);
      } else if ((var57 == 0)) {
        traffic_assert(true);
        traffic_assert(true);
        int const105 = -1;
        int var132 = sf_fuzz_writef_double((*out32), const105);
        traffic_assert(true);
        int var175 = sf_current_byterate((*out32));
        traffic_assert(true);
        char* var218 = sf_strerror((*out32));
        traffic_assert(true);
        int const225 = 0;
        int var261 = sf_fuzz_readf_int((*out32), const225);
        traffic_assert(true);
        int var304 = sf_fuzz_readf_double((*out32), var132);
        traffic_assert(true);
      }
    } else {
    }
  }
}