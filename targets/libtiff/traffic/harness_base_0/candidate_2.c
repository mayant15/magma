#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_2(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  uint8_t* null36 = NULL;
  int var49 = tiff_fuzz_write_strip(var24, null36, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var77 = TIFFSetField(var24, size, var49);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var105 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var131 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var157 = TIFFWriteDirectory(var24);
  traffic_assert(true);
}