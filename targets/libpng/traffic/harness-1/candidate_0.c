#include <traffic.h>

#include <png-support.h>

#include <png.h>

int fuzz_0(uint8_t* data, int size) {
  png_image* var4 = png_fuzz_new_image();
  if (!((var4 == NULL))) {
    traffic_assert(true);
    int var13 = png_image_begin_read_from_memory(var4, data, size);
    if (!((var13 == 0))) {
      traffic_assert(true);
      png_color* null21 = NULL;
      uint8_t* null23 = NULL;
      int const24 = 0;
      uint8_t* null27 = NULL;
      int var29 = png_image_finish_read(var4, null21, null23, const24, null27);
      traffic_assert(true);
      png_fuzz_free_image(var4);
    } else if ((var13 == 0)) {
      traffic_assert(true);
    }
  } else if ((var4 == NULL)) {
  }
}