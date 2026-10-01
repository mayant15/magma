#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_0(uint8_t* data, int size) {
  char* var35 = sf_version_string();
  int const57 = 1;
  char* var71 = sf_error_number(const57);
  traffic_assert(true);
  char* var108 = sf_error_number(size);
  traffic_assert(true);
}