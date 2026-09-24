#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_1(uint8_t* data, int size) {
  png_image* var20 = png_fuzz_new_image();
  png_image* null24 = NULL;
  int var41 = png_image_begin_read_from_memory(null24, data, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_color out55_slot; png_color* out55 = &out55_slot;
  uint8_t out61_slot; uint8_t* out61 = &out61_slot;
  int var65 = png_image_finish_read(var20, out55, data, size, out61);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var91 = png_image_begin_read_from_memory(var20, data, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_image_free(var20);
  traffic_assert(true);
  png_color* null127 = NULL;
  uint8_t out128_slot; uint8_t* out128 = &out128_slot;
  uint8_t out132_slot; uint8_t* out132 = &out132_slot;
  int var136 = png_image_finish_read(var20, null127, out128, size, out132);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}