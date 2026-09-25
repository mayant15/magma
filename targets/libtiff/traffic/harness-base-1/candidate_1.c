#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_1(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int var49 = tiff_fuzz_read_strip(var24);
  traffic_assert(true);
  TIFFClose(var24);
  traffic_assert(true);
  TIFF* var100 = tiff_open_r(data, size);
  traffic_assert(true);
  traffic_assert(true);
  int var127 = tiff_fuzz_read_rgba(var100);
  traffic_assert(true);
  TIFFClose(var100);
  traffic_assert(true);
}