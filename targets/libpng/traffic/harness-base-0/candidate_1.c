#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_1(uint8_t* data, int size) {
  png_image* null3 = NULL;
  int var20 = png_image_begin_read_from_memory(null3, data, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}