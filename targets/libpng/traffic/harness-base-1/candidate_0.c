#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_0(uint8_t* data, int size) {
  png_image* var20 = png_fuzz_new_image();
  png_color out31_slot; png_color* out31 = &out31_slot;
  uint8_t out33_slot; uint8_t* out33 = &out33_slot;
  uint8_t* null38 = NULL;
  int var41 = png_image_finish_read(var20, out31, out33, size, null38);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_image* null56 = NULL;
  png_color* null58 = NULL;
  uint8_t* null60 = NULL;
  int const61 = -1;
  int var67 = png_image_finish_read(null56, null58, null60, const61, out33);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}