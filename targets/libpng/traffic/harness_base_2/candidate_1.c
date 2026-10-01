#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_1(uint8_t* data, int size) {
  png_image* null9 = NULL;
  png_color* null11 = NULL;
  uint8_t* null13 = NULL;
  uint8_t out16_slot; uint8_t* out16 = &out16_slot;
  int var20 = png_image_finish_read(null9, null11, null13, size, out16);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const32 = 0;
  int var46 = png_image_begin_read_from_memory(null9, out16, const32);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}