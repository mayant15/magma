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
  png_fuzz_free_image(null24);
  traffic_assert(true);
  uint8_t out70_slot; uint8_t* out70 = &out70_slot;
  int const72 = 1;
  int var86 = png_image_begin_read_from_memory(var20, out70, const72);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var110 = png_image_begin_read_from_memory(var20, out70, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}