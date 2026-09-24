#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_0(uint8_t* data, int size) {
  char* var35 = sf_error_number(size);
  traffic_assert(true);
  char* var72 = sf_version_string();
}