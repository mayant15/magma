#include <traffic.h>

#include <png.h>

int LLVMFuzzerTestOneInput(uint8_t* data, int size) {
  FuzzedDataProvider* fdp = traffic_provider_init(data, size);
  int var0 = png_access_version_number();
}