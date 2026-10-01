#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  SF_INFO out16_slot; SF_INFO* out16 = &out16_slot;
  int var25 = sf_format_check(out16);
  char* var55 = sf_version_string();
  if ((var25 == 1)) {
    traffic_assert(true);
    SndFileP out92_slot; SndFileP* out92 = &out92_slot;
    VIO_DATA out93_slot; VIO_DATA* out93 = &out93_slot;
    SF_VIRTUAL_IO out94_slot; SF_VIRTUAL_IO* out94 = &out94_slot;
    if (!((out16 == NULL))) {
      int var117 = sf_init_file(data, size, out92, out93, out94, out16);
      if (!((var117 == 0))) {
        traffic_assert(true);
        char* var189 = sf_strerror((*out92));
        traffic_assert(true);
      } else if ((var117 == 0)) {
        traffic_assert(true);
        traffic_assert(true);
        int const129 = 1;
        int var162 = sf_fuzz_writef_int((*out92), const129);
        traffic_assert(true);
        int var232 = sf_fuzz_writef_int((*out92), var162);
        traffic_assert(true);
        int const265 = 0;
        int var275 = sf_seek((*out92), var232, const265);
        traffic_assert(true);
        int var318 = sf_error((*out92));
        traffic_assert(true);
        traffic_assert(true);
        char* var361 = sf_strerror((*out92));
        traffic_assert(true);
        int var404 = sf_fuzz_readf_double((*out92), var275);
        traffic_assert(true);
        int const414 = -1;
        int var447 = sf_fuzz_writef_int((*out92), const414);
        traffic_assert(true);
        int var490 = sf_fuzz_readf_int((*out92), var447);
        traffic_assert(true);
        int var533 = sf_close((*out92));
        traffic_assert(true);
      }
    } else {
    }
  } else if (!((var25 == 1))) {
    traffic_assert(true);
    SndFileP out62_slot; SndFileP* out62 = &out62_slot;
    VIO_DATA out63_slot; VIO_DATA* out63 = &out63_slot;
    SF_VIRTUAL_IO out64_slot; SF_VIRTUAL_IO* out64 = &out64_slot;
    if (!((out16 == NULL))) {
      int var87 = sf_init_file(data, size, out62, out63, out64, out16);
    } else {
    }
  }
}