#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_4(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int var49 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var75 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  TIFF* var101 = tiff_open_r(data, size);
  traffic_assert(true);
  traffic_assert(true);
  int const122 = 1;
  int const124 = 0;
  int var128 = TIFFSetField(var101, const122, const124);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var156 = tiff_fuzz_read_rgba(var101);
  traffic_assert(true);
  TIFFClose(var101);
  traffic_assert(true);
}