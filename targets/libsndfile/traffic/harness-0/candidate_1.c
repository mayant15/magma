#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  char* var25 = sf_version_string();
  SndFileP out30_slot; SndFileP* out30 = &out30_slot;
  VIO_DATA out31_slot; VIO_DATA* out31 = &out31_slot;
  SF_VIRTUAL_IO out32_slot; SF_VIRTUAL_IO* out32 = &out32_slot;
  SF_INFO out33_slot; SF_INFO* out33 = &out33_slot;
  int var55 = sf_init_file(data, size, out30, out31, out32, out33);
  if (!((var55 == 0))) {
    traffic_assert(true);
    char* var127 = sf_strerror((*out30));
    traffic_assert(true);
    int var154 = sf_error((*out30));
    traffic_assert(true);
    traffic_assert(true);
    char* var223 = sf_error_number(var154);
  } else if ((var55 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    int const88 = 1;
    int const90 = 1;
    int var100 = sf_seek((*out30), const88, const90);
    traffic_assert(true);
    TF_String const173 = "e%%7g@yMlyf2!(!@";
    SF_CHUNK_ITERATOR* var197 = sf_fuzz_get_chunk_iterator((*out30), const173);
  }
}