#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_1(uint8_t* data, int size) {
  png_image* null19 = NULL;
  png_image_free(null19);
  traffic_assert(true);
  png_image* var41 = png_fuzz_new_image();
  uint8_t* null47 = NULL;
  int const48 = 0;
  int var62 = png_image_begin_read_from_memory(var41, null47, const48);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_color* null77 = NULL;
  int var86 = png_image_finish_read(var41, null77, null47, var62, data);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  uint8_t out96_slot; uint8_t* out96 = &out96_slot;
  int const98 = 1;
  int var112 = png_image_begin_read_from_memory(var41, out96, const98);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  uint8_t* null133 = NULL;
  int var136 = png_image_finish_read(var41, null77, data, const98, null133);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const148 = -1;
  int var162 = png_image_begin_read_from_memory(var41, data, const148);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_image_free(var41);
  traffic_assert(true);
  png_color out197_slot; png_color* out197 = &out197_slot;
  uint8_t out199_slot; uint8_t* out199 = &out199_slot;
  int const201 = 1;
  uint8_t* null204 = NULL;
  int var207 = png_image_finish_read(var41, out197, out199, const201, null204);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}