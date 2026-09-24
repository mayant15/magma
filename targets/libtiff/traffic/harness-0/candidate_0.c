#include <traffic.h>

#include <tiff-support.h>

#include <tiffio.h>

int fuzz_0(uint8_t* data, int size) {
  TIFF* var9 = tiff_open_r(data, size);
  if (!((var9 == NULL))) {
    traffic_assert(true);
    int var18 = tiff_fuzz_read_rgba(var9);
    traffic_assert(true);
    TIFFClose(var9);
  } else if ((var9 == NULL)) {
  }
}