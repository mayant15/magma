#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_1(uint8_t* data, int size) {
  png_image* var20 = png_fuzz_new_image();
  png_image* null40 = NULL;
  png_image_free(null40);
  traffic_assert(true);
  png_image_free(var20);
  traffic_assert(true);
  int const69 = 1;
  int var83 = png_image_begin_read_from_memory(var20, data, const69);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_color* null98 = NULL;
  uint8_t out99_slot; uint8_t* out99 = &out99_slot;
  uint8_t* null104 = NULL;
  int var107 = png_image_finish_read(var20, null98, out99, const69, null104);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_image* null122 = NULL;
  uint8_t* null126 = NULL;
  int var133 = png_image_finish_read(null122, null98, null126, var83, null104);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}