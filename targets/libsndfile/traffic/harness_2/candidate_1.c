#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_1(uint8_t* data, int size) {
  char* var29 = sf_version_string();
  SndFileP out34_slot; SndFileP* out34 = &out34_slot;
  VIO_DATA out35_slot; VIO_DATA* out35 = &out35_slot;
  SF_VIRTUAL_IO out36_slot; SF_VIRTUAL_IO* out36 = &out36_slot;
  SF_INFO out37_slot; SF_INFO* out37 = &out37_slot;
  int var59 = sf_init_file(data, size, out34, out35, out36, out37);
  if (!((var59 == 0))) {
    traffic_assert(true);
    int var88 = sf_error((*out34));
    traffic_assert(true);
    traffic_assert(true);
    char* var115 = sf_strerror((*out34));
    traffic_assert(true);
  } else if ((var59 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    int const125 = -1;
    int var158 = sf_fuzz_writef_int((*out34), const125);
    traffic_assert(true);
    int var201 = sf_fuzz_writef_int((*out34), var158);
    traffic_assert(true);
    int const208 = 1;
    int var244 = sf_fuzz_readf_int((*out34), const208);
    traffic_assert(true);
    char* var287 = sf_strerror((*out34));
    traffic_assert(true);
    int var330 = sf_error((*out34));
    traffic_assert(true);
    traffic_assert(true);
    if (((var330 == 0) || ((var330 == 1) || (var330 == 2)))) {
      int var373 = sf_seek((*out34), var244, var330);
      traffic_assert(true);
      int const380 = -1;
      int var416 = sf_fuzz_readf_int((*out34), const380);
      traffic_assert(true);
      int var459 = sf_fuzz_readf_int((*out34), var373);
      traffic_assert(true);
      if (((var459 == 0) || ((var459 == 1) || (var459 == 2)))) {
        int var502 = sf_seek((*out34), var416, var459);
        traffic_assert(true);
        int var545 = sf_current_byterate((*out34));
        traffic_assert(true);
        int var588 = sf_close((*out34));
        traffic_assert(true);
      } else {
      }
    } else {
    }
  }
}