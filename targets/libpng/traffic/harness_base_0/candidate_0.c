#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_0(uint8_t* data, int size) {
  png_image* null19 = NULL;
  png_image_free(null19);
  traffic_assert(true);
}