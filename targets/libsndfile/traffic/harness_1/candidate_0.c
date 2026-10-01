#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_0(uint8_t* data, int size) {
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
        int var232 = sf_error((*out92));
        traffic_assert(true);
        traffic_assert(true);
        char* var259 = sf_error_number(var232);
      } else if ((var117 == 0)) {
        traffic_assert(true);
        traffic_assert(true);
        int const129 = 1;
        int var162 = sf_fuzz_writef_int((*out92), const129);
        traffic_assert(true);
        int var205 = sf_fuzz_writef_double((*out92), var162);
        traffic_assert(true);
        TF_String const277 = "DfLc%1#fsg";
        SF_CHUNK_ITERATOR* var301 = sf_fuzz_get_chunk_iterator((*out92), const277);
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