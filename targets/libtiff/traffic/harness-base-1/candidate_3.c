#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_3(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int const45 = 1;
  int var49 = TIFFSetField(var24, size, const45);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const55 = 0;
  TIFF* var77 = tiff_open_r(data, const55);
  traffic_assert(true);
  traffic_assert(true);
  int var104 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var130 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var156 = TIFFWriteDirectory(var24);
  traffic_assert(true);
}