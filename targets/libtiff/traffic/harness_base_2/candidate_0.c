#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_0(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_r(data, size);
  traffic_assert(true);
  traffic_assert(true);
  TIFFClose(var24);
  traffic_assert(true);
}