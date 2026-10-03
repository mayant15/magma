#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_0(uint8_t* data, int size) {
  png_image* null9 = NULL;
  png_color* null11 = NULL;
  uint8_t out16_slot; uint8_t* out16 = &out16_slot;
  int var20 = png_image_finish_read(null9, null11, data, size, out16);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_image* null29 = NULL;
  uint8_t out30_slot; uint8_t* out30 = &out30_slot;
  int const32 = 0;
  int var46 = png_image_begin_read_from_memory(null29, out30, const32);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}