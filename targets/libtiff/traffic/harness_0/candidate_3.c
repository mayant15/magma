#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_3(uint8_t* data, int size) {
  TIFF* var9 = tiff_open_w();
  TIFF* var19 = tiff_open_r(data, size);
  if (!((var19 == NULL))) {
    traffic_assert(true);
    if (!((var9 == NULL))) {
      traffic_assert(true);
      int var33 = tiff_fuzz_read_rgba(var19);
      traffic_assert(true);
      TIFFClose(var19);
    } else if ((var9 == NULL)) {
    }
  } else if ((var19 == NULL)) {
  }
}