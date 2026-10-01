#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_2(uint8_t* data, int size) {
  png_image* null3 = NULL;
  uint8_t out4_slot; uint8_t* out4 = &out4_slot;
  int var20 = png_image_begin_read_from_memory(null3, out4, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}