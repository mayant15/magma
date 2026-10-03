#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_2(uint8_t* data, int size) {
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
    int var110 = sf_error((*out30));
    traffic_assert(true);
    traffic_assert(true);
    if ((var84 == 1)) {
      traffic_assert(true);
    } else if (!((var84 == 1))) {
      traffic_assert(true);
    }
  } else if ((var55 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    int const126 = 0;
    int var153 = sf_fuzz_writef_double((*out30), const126);
    traffic_assert(true);
    TF_String const174 = "TpdusNQ#MiCM";
    SF_CHUNK_ITERATOR* var198 = sf_fuzz_get_chunk_iterator((*out30), const174);
  }
}