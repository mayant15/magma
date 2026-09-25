#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_0(uint8_t* data, int size) {
  int const2 = 0;
  TIFF* var24 = tiff_open_r(data, const2);
  traffic_assert(true);
  traffic_assert(true);
}