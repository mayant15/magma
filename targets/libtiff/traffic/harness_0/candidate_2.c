#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_2(uint8_t* data, int size) {
  TIFF* var9 = tiff_open_w();
  TIFF* var19 = tiff_open_r(data, size);
  if (!((var9 == NULL))) {
    traffic_assert(true);
    if (!((var19 == NULL))) {
      traffic_assert(true);
      TIFFClose(var19);
    } else if ((var19 == NULL)) {
    }
  } else if ((var9 == NULL)) {
    if (!((var19 == NULL))) {
      traffic_assert(true);
    } else if ((var19 == NULL)) {
    }
  }
}