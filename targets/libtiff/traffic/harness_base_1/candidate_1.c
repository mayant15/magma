#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_1(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int const45 = 1;
  int var49 = TIFFSetField(var24, size, const45);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TIFF* var77 = tiff_open_r(data, size);
  traffic_assert(true);
  traffic_assert(true);
  TIFFClose(var77);
  traffic_assert(true);
}