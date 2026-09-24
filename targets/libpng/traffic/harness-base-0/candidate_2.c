#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_2(uint8_t* data, int size) {
  png_image* null19 = NULL;
  png_image_free(null19);
  traffic_assert(true);
  png_image* null30 = NULL;
  png_color out31_slot; png_color* out31 = &out31_slot;
  uint8_t* null34 = NULL;
  int const35 = 1;
  uint8_t out37_slot; uint8_t* out37 = &out37_slot;
  int var41 = png_image_finish_read(null30, out31, null34, const35, out37);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}