#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_0(uint8_t* data, int size) {
  char* var29 = sf_version_string();
  SF_INFO out43_slot; SF_INFO* out43 = &out43_slot;
  int var59 = sf_format_check(out43);
  SndFileP out64_slot; SndFileP* out64 = &out64_slot;
  VIO_DATA out65_slot; VIO_DATA* out65 = &out65_slot;
  SF_VIRTUAL_IO out66_slot; SF_VIRTUAL_IO* out66 = &out66_slot;
  SF_INFO out67_slot; SF_INFO* out67 = &out67_slot;
  int var89 = sf_init_file(data, size, out64, out65, out66, out67);
  if (!((var89 == 0))) {
    traffic_assert(true);
    int var237 = sf_error((*out64));
    traffic_assert(true);
    char* var263 = sf_error_number(var237);
  } else if ((var89 == 0)) {
    traffic_assert(true);
    traffic_assert(true);
    int const123 = 1;
    int const125 = 1;
    int var138 = sf_seek((*out64), const123, const125);
    traffic_assert(true);
    char* var185 = sf_strerror((*out64));
    if (!((out67 == NULL))) {
      int var211 = sf_format_check(out67);
    } else {
    }
  }
}