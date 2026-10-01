#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_5(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int var49 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var75 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  TIFF* var101 = tiff_open_r(data, size);
  traffic_assert(true);
  traffic_assert(true);
  int var128 = tiff_fuzz_write_strip(var101, data, var49);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TIFFClose(var101);
  traffic_assert(true);
}