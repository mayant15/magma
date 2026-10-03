#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_3(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  uint8_t* null36 = NULL;
  int var49 = tiff_fuzz_write_strip(var24, null36, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const73 = -1;
  int var77 = TIFFSetField(var24, var49, const73);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TIFF* var105 = tiff_open_r(data, size);
  traffic_assert(true);
  traffic_assert(true);
  int var132 = TIFFWriteDirectory(var105);
  traffic_assert(true);
  TIFFClose(var105);
  traffic_assert(true);
}