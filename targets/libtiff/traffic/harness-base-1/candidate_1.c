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
  int const55 = 0;
  TIFF* var77 = tiff_open_r(data, const55);
  traffic_assert(true);
  traffic_assert(true);
  int var104 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  uint8_t* null117 = NULL;
  int const118 = 1;
  int var130 = tiff_fuzz_write_strip(var24, null117, const118);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}