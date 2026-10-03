#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_4(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int const37 = 0;
  int var49 = tiff_fuzz_write_strip(var24, data, const37);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TIFFClose(var24);
  traffic_assert(true);
}