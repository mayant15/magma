#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_1(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int var49 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var75 = tiff_fuzz_write_strip(var24, data, var49);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const99 = 1;
  int var103 = TIFFSetField(var24, var75, const99);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}