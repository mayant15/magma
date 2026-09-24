#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_2(uint8_t* data, int size) {
  png_image* var20 = png_fuzz_new_image();
  uint8_t* null26 = NULL;
  int const27 = 1;
  int var41 = png_image_begin_read_from_memory(var20, null26, const27);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  uint8_t out49_slot; uint8_t* out49 = &out49_slot;
  int const51 = 1;
  int var65 = png_image_begin_read_from_memory(var20, out49, const51);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var89 = png_image_begin_read_from_memory(var20, out49, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}