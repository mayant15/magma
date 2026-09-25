#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_3(uint8_t* data, int size) {
  png_image* var20 = png_fuzz_new_image();
  png_color out31_slot; png_color* out31 = &out31_slot;
  int const35 = 0;
  uint8_t* null38 = NULL;
  int var41 = png_image_finish_read(var20, out31, data, const35, null38);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_color out57_slot; png_color* out57 = &out57_slot;
  int const61 = -1;
  uint8_t out63_slot; uint8_t* out63 = &out63_slot;
  int var67 = png_image_finish_read(var20, out57, data, const61, out63);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const79 = 1;
  int var93 = png_image_begin_read_from_memory(var20, data, const79);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  uint8_t* null102 = NULL;
  int const103 = 0;
  int var117 = png_image_begin_read_from_memory(var20, null102, const103);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var141 = png_image_begin_read_from_memory(var20, out63, const61);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const151 = -1;
  int var165 = png_image_begin_read_from_memory(var20, data, const151);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_fuzz_free_image(var20);
  traffic_assert(true);
}