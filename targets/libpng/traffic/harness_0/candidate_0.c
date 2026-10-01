#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_0(uint8_t* data, int size) {
  png_image* var4 = png_fuzz_new_image();
  if (!((var4 == NULL))) {
    traffic_assert(true);
    png_fuzz_free_image(var4);
  } else if ((var4 == NULL)) {
  }
}