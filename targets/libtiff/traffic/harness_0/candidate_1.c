#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_1(uint8_t* data, int size) {
  TIFF* var9 = tiff_open_w();
  TIFF* var19 = tiff_open_r(data, size);
  if (!((var9 == NULL))) {
    traffic_assert(true);
    int const28 = 278;
    int const30 = 0;
    int var33 = TIFFSetField(var9, const28, const30);
  } else if ((var9 == NULL)) {
    if (!((var19 == NULL))) {
      traffic_assert(true);
    } else if ((var19 == NULL)) {
    }
  }
}