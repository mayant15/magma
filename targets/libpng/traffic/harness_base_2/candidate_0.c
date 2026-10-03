#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_0(uint8_t* data, int size) {
  png_image* null19 = NULL;
  png_image_free(null19);
  traffic_assert(true);
  png_color* null32 = NULL;
  uint8_t out33_slot; uint8_t* out33 = &out33_slot;
  uint8_t* null38 = NULL;
  int var41 = png_image_finish_read(null19, null32, out33, size, null38);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  uint8_t out51_slot; uint8_t* out51 = &out51_slot;
  int var67 = png_image_begin_read_from_memory(null19, out51, var41);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}