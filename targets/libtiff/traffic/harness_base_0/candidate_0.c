#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_0(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_w();
  int const27 = 0;
  TIFF* var49 = tiff_open_r(data, const27);
  traffic_assert(true);
  traffic_assert(true);
  int var76 = tiff_fuzz_read_rgba(var24);
  traffic_assert(true);
  int var102 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  TIFFClose(var24);
  traffic_assert(true);
}