#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_2(uint8_t* data, int size) {
  png_image* null9 = NULL;
  png_color* null11 = NULL;
  uint8_t out12_slot; uint8_t* out12 = &out12_slot;
  int var20 = png_image_finish_read(null9, null11, out12, size, data);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}