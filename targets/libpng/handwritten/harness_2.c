/* Simplified (png_image) read API.
 *
 * Every png_image_free of a live image goes through png_safe_execute, so any
 * input that gets past png_image_read_init hits PNG002. png_image_read_direct
 * always calls png_set_expand, so a palette image with an empty PLTE hits
 * PNG007. The output format is picked from the input's last byte (the IEND
 * CRC in a well-formed file), so seeds are used as-is.
 *
 *   PNG002  png_image_free -> png_safe_execute(png_image_free_function)
 *   PNG007  palette image with a zero-length PLTE (valid CRC needed here)
 *   also reaches PNG001, PNG003, PNG005, PNG006 through png_read_info
 */

#include "harness.h"

static const png_uint_32 formats[] = {
    PNG_FORMAT_RGBA,        PNG_FORMAT_RGB,        PNG_FORMAT_GRAY,
    PNG_FORMAT_GA,          PNG_FORMAT_BGRA,       PNG_FORMAT_ARGB,
    PNG_FORMAT_LINEAR_RGB_ALPHA, PNG_FORMAT_LINEAR_Y,
    PNG_FORMAT_RGBA_COLORMAP, PNG_FORMAT_RGB_COLORMAP,
    PNG_FORMAT_GRAY | PNG_FORMAT_FLAG_COLORMAP,
};

#define NUM_FORMATS (sizeof formats / sizeof formats[0])

/* Output image buffer cap; the simplified API writes every pixel. */
#define MAX_IMAGE_BYTES ((size_t)256 << 20)

static int fuzz_one(const uint8_t *data, size_t size) {
  png_image image;
  void *buffer = NULL, *colormap = NULL;
  size_t image_size;

  if (size < 8)
    return 0;

  memset(&image, 0, sizeof image);
  image.version = PNG_IMAGE_VERSION;

  if (!png_image_begin_read_from_memory(&image, data, size))
    return 0; /* image already freed by libpng */

  image.format = formats[data[size - 1] % NUM_FORMATS];

  image_size = PNG_IMAGE_SIZE(image);
  if (image_size == 0 || image_size > MAX_IMAGE_BYTES) {
    png_image_free(&image);
    return 0;
  }

  buffer = malloc(image_size);
  if (image.format & PNG_FORMAT_FLAG_COLORMAP)
    colormap = malloc(PNG_IMAGE_COLORMAP_SIZE(image));

  if (buffer != NULL &&
      (colormap != NULL || !(image.format & PNG_FORMAT_FLAG_COLORMAP)))
    (void)png_image_finish_read(&image, NULL, buffer, 0, colormap);

  /* No-op if finish_read already released it. */
  png_image_free(&image);
  free(buffer);
  free(colormap);
  return 0;
}
