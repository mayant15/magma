#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_8(uint8_t* data, int size) {
  SF_INFO out16_slot; SF_INFO* out16 = &out16_slot;
  int var25 = sf_format_check(out16);
  if ((var25 == 1)) {
    traffic_assert(true);
    SndFileP out65_slot; SndFileP* out65 = &out65_slot;
    VIO_DATA out66_slot; VIO_DATA* out66 = &out66_slot;
    SF_VIRTUAL_IO out67_slot; SF_VIRTUAL_IO* out67 = &out67_slot;
    SF_INFO out68_slot; SF_INFO* out68 = &out68_slot;
    int var90 = sf_init_file(data, size, out65, out66, out67, out68);
    if (!((var90 == 0))) {
      traffic_assert(true);
      char* var204 = sf_strerror((*out65));
      traffic_assert(true);
    } else if ((var90 == 0)) {
      traffic_assert(true);
      traffic_assert(true);
      TF_String const154 = "auW[DGekV#8l4lY%[";
      SF_CHUNK_ITERATOR* var178 = sf_fuzz_get_chunk_iterator((*out65), const154);
      if (!((var178 == NULL))) {
        traffic_assert(true);
        traffic_assert(true);
      } else if ((var178 == NULL)) {
        traffic_assert(true);
        int const349 = -1;
        int var379 = sf_fuzz_readf_double((*out65), const349);
        traffic_assert(true);
        int var465 = sf_current_byterate((*out65));
        traffic_assert(true);
        int const496 = 1;
        if (((var379 == 0) || ((var379 == 1) || (var379 == 2)))) {
          int var508 = sf_seek((*out65), const496, var379);
          traffic_assert(true);
        } else {
        }
      }
    }
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
        int var132 = sf_error((*out32));
        traffic_assert(true);
        traffic_assert(true);
        int var250 = sf_fuzz_writef_int((*out32), var132);
        traffic_assert(true);
        int const266 = 1;
        int var293 = sf_fuzz_writef_double((*out32), const266);
        traffic_assert(true);
        int const324 = -1;
        if (((var293 == 0) || ((var293 == 1) || (var293 == 2)))) {
          int var336 = sf_seek((*out32), const324, var293);
          traffic_assert(true);
          int const389 = 1;
          int var422 = sf_fuzz_writef_int((*out32), const389);
          traffic_assert(true);
        } else {
        }
      }
    } else {
    }
  }
}