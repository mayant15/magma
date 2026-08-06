#include <traffic.h>

#include <sndfile_fuzzer.h>

#include <sndfile.h>

int LLVMFuzzerTestOneInput(uint8_t* data, int size) {
  char* var63 = sf_version_string();
  SF_INFO out125_slot; SF_INFO* out125 = &out125_slot; 
  int var127 = sf_format_check(out125);
  if ((var127 == 1)) {
    traffic_assert(true);
  } else if (!((var127 == 1))) {
    traffic_assert(true);
    SndFileP out161_slot; SndFileP* out161 = &out161_slot; 
    VIO_DATA out163_slot; VIO_DATA* out163 = &out163_slot; 
    SF_VIRTUAL_IO out165_slot; SF_VIRTUAL_IO* out165 = &out165_slot; 
    SF_INFO out167_slot; SF_INFO* out167 = &out167_slot; 
    int var193 = sf_init_file(data, size, out161, out163, out165, out167);
    if (!((var193 == 0))) {
      traffic_assert(true);
      char* var373 = sf_strerror((*out161));
    } else if ((var193 == 0)) {
      traffic_assert(true);
      traffic_assert(true);
      int* null205 = NULL;
      int const207 = 0;
      int var212 = sf_writef_int((*out161), null205, const207);
      traffic_assert(true);
      int var259 = sf_close((*out161));
      traffic_assert(true);
      char* var323 = sf_error_number(var259);
      int var357 = sf_format_check(out167);
    }
  }
}