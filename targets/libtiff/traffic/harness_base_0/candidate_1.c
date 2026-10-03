#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_1(uint8_t* data, int size) {
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
  uint8_t* null82 = NULL;
  TIFF* var105 = tiff_open_r(null82, var77);
  traffic_assert(true);
  traffic_assert(true);
  int var132 = tiff_fuzz_read_rgba(var24);
  traffic_assert(true);
}