#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_4(uint8_t* data, int size) {
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
      int var204 = sf_error((*out65));
      traffic_assert(true);
      traffic_assert(true);
      char* var302 = sf_error_number(var204);
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
        int var247 = sf_close((*out32));
        traffic_assert(true);
        char* var273 = sf_error_number(var132);
      }
    } else {
    }
  }
}