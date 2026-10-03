#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_3(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_r(data, size);
  traffic_assert(true);
  traffic_assert(true);
  int const47 = -1;
  int var51 = TIFFSetField(var24, size, const47);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var79 = tiff_fuzz_read_rgba(var24);
  traffic_assert(true);
  TIFFClose(var24);
  traffic_assert(true);
}