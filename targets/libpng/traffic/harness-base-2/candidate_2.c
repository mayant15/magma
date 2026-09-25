#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_2(uint8_t* data, int size) {
  png_image* var20 = png_fuzz_new_image();
  png_image_free(var20);
  traffic_assert(true);
  int var62 = png_image_begin_read_from_memory(var20, data, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  uint8_t out70_slot; uint8_t* out70 = &out70_slot;
  int const72 = -1;
  int var86 = png_image_begin_read_from_memory(var20, out70, const72);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var110 = png_image_begin_read_from_memory(var20, data, var62);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var134 = png_image_begin_read_from_memory(var20, data, var86);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  png_color* null149 = NULL;
  int const152 = 1;
  uint8_t out154_slot; uint8_t* out154 = &out154_slot;
  int var158 = png_image_finish_read(var20, null149, out70, const152, out154);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  uint8_t out180_slot; uint8_t* out180 = &out180_slot;
  int var184 = png_image_finish_read(var20, null149, data, var134, out180);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const196 = -1;
  int var210 = png_image_begin_read_from_memory(var20, out70, const196);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}