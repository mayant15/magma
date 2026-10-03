#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_2(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_r(data, size);
  traffic_assert(true);
  traffic_assert(true);
  int const45 = -1;
  int const47 = 0;
  int var51 = TIFFSetField(var24, const45, const47);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}