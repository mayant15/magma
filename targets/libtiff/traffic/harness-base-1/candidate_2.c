#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_2(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_r(data, size);
  traffic_assert(true);
  traffic_assert(true);
  int var51 = tiff_fuzz_read_strip(var24);
  traffic_assert(true);
  int var77 = tiff_fuzz_read_strip(var24);
  traffic_assert(true);
  int var103 = tiff_fuzz_read_rgba(var24);
  traffic_assert(true);
  int var129 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int const149 = -1;
  int const151 = 0;
  int var155 = TIFFSetField(var24, const149, const151);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}