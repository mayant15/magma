#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_2(uint8_t* data, int size) {
  png_image* null9 = NULL;
  png_color* null11 = NULL;
  uint8_t out16_slot; uint8_t* out16 = &out16_slot;
  int var20 = png_image_finish_read(null9, null11, data, size, out16);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_image* var46 = png_fuzz_new_image();
  png_image_free(var46);
  traffic_assert(true);
  int var88 = png_image_begin_read_from_memory(var46, data, var20);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var112 = png_image_begin_read_from_memory(var46, data, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_image_free(var46);
  traffic_assert(true);
  uint8_t* null150 = NULL;
  int var157 = png_image_finish_read(var46, null11, null150, var88, out16);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}