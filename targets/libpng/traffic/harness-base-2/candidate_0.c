#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_0(uint8_t* data, int size) {
  png_image* var20 = png_fuzz_new_image();
  png_image* null30 = NULL;
  png_color* null32 = NULL;
  int const35 = 0;
  uint8_t out37_slot; uint8_t* out37 = &out37_slot;
  int var41 = png_image_finish_read(null30, null32, data, const35, out37);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_color out57_slot; png_color* out57 = &out57_slot;
  int const61 = 0;
  int var67 = png_image_finish_read(var20, out57, data, const61, out37);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}