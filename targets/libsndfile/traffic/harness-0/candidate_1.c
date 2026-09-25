#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  char* var25 = sf_version_string();
  SF_INFO out46_slot; SF_INFO* out46 = &out46_slot;
  int var55 = sf_format_check(out46);
  SndFileP out60_slot; SndFileP* out60 = &out60_slot;
  VIO_DATA out61_slot; VIO_DATA* out61 = &out61_slot;
  SF_VIRTUAL_IO out62_slot; SF_VIRTUAL_IO* out62 = &out62_slot;
  SF_INFO out63_slot; SF_INFO* out63 = &out63_slot;
  int var85 = sf_init_file(data, size, out60, out61, out62, out63);
  if (!((var85 == 0))) {
    traffic_assert(true);
    int var114 = sf_error((*out60));
    traffic_assert(true);
    traffic_assert(true);
    char* var184 = sf_error_number(var114);
    char* var210 = sf_strerror((*out60));
    traffic_assert(true);
  } else if ((var85 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    int var157 = sf_current_byterate((*out60));
    traffic_assert(true);
    TF_String const229 = "n(oOLHC]v7uezxb0fUd";
    SF_CHUNK_ITERATOR* var253 = sf_fuzz_get_chunk_iterator((*out60), const229);
    if (!((var253 == NULL))) {
      traffic_assert(true);
      traffic_assert(true);
    } else if ((var253 == NULL)) {
      traffic_assert(true);
      int var298 = sf_fuzz_writef_double((*out60), var157);
      traffic_assert(true);
      int var341 = sf_fuzz_writef_double((*out60), var298);
      traffic_assert(true);
      int var384 = sf_fuzz_writef_int((*out60), var341);
      traffic_assert(true);
      int const415 = -1;
      if (((var384 == 0) || ((var384 == 1) || (var384 == 2)))) {
        int var427 = sf_seek((*out60), const415, var384);
        traffic_assert(true);
        int const434 = 1;
        int var470 = sf_fuzz_readf_int((*out60), const434);
        traffic_assert(true);
        int const477 = -1;
        int var513 = sf_fuzz_readf_int((*out60), const477);
        traffic_assert(true);
        int var556 = sf_fuzz_readf_int((*out60), var470);
        traffic_assert(true);
        int var599 = sf_fuzz_readf_double((*out60), var556);
        traffic_assert(true);
        int const632 = 1;
        int var642 = sf_seek((*out60), var427, const632);
        traffic_assert(true);
        int const652 = -1;
        int var685 = sf_fuzz_writef_int((*out60), const652);
        traffic_assert(true);
        int var728 = sf_fuzz_writef_int((*out60), var599);
        traffic_assert(true);
        int var771 = sf_fuzz_readf_double((*out60), var642);
        traffic_assert(true);
      } else {
      }
    }
  }
}