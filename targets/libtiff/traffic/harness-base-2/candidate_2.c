#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_2(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int var49 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var75 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var101 = TIFFWriteDirectory(var24);
  traffic_assert(true);
}