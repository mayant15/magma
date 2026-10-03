#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_5(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int const37 = 0;
  int var49 = tiff_fuzz_write_strip(var24, data, const37);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var77 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var103 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var129 = TIFFWriteDirectory(var24);
  traffic_assert(true);
}