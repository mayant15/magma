#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_0(uint8_t* data, int size) {
  TIFF* var9 = tiff_open_r(data, size);
  TIFF* var17 = tiff_open_w();
  if (!((var9 == NULL))) {
    traffic_assert(true);
    int var26 = tiff_fuzz_read_rgba(var9);
    traffic_assert(true);
    TIFFClose(var9);
    if (!((var17 == NULL))) {
      traffic_assert(true);
      TIFFClose(var17);
    } else if ((var17 == NULL)) {
    }
  } else if ((var9 == NULL)) {
  }
}