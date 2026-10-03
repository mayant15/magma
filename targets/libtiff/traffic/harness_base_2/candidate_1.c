#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_1(uint8_t* data, int size) {
  TIFF* var24 = tiff_open_r(data, size);
  traffic_assert(true);
  traffic_assert(true);
  int const47 = -1;
  int var51 = TIFFSetField(var24, size, const47);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var79 = TIFFWriteDirectory(var24);
  traffic_assert(true);
  int var105 = tiff_fuzz_read_strip(var24);
  traffic_assert(true);
  int const109 = 0;
  TIFF* var131 = tiff_open_r(data, const109);
  traffic_assert(true);
  traffic_assert(true);
  uint8_t out144_slot; uint8_t* out144 = &out144_slot;
  int const146 = 1;
  int var158 = tiff_fuzz_write_strip(var24, out144, const146);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}