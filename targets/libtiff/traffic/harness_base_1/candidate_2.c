#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_2(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int const27 = 0;
  TIFF* var49 = tiff_open_r(data, const27);
  traffic_assert(true);
  traffic_assert(true);
  int var76 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var102 = tiff_fuzz_read_strip(var24);
  traffic_assert(true);
  int var128 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var154 = TIFFWriteDirectory(var24);
  traffic_assert(true);
}