#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_0(uint8_t* data, int size) {
  png_image* null1 = NULL;
  png_fuzz_free_image(null1);
  traffic_assert(true);
}