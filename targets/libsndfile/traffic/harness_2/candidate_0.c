#include <traffic.h>

#include <sndfile-support.h>

#include <sndfile.h>

int fuzz_0(uint8_t* data, int size) {
  char* var29 = sf_version_string();
  SF_INFO out50_slot; SF_INFO* out50 = &out50_slot;
  int var59 = sf_format_check(out50);
}