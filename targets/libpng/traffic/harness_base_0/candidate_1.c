#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_1(uint8_t* data, int size) {
  png_image* var20 = png_fuzz_new_image();
  png_fuzz_free_image(var20);
  traffic_assert(true);
  png_image* null61 = NULL;
  png_image_free(null61);
  traffic_assert(true);
}