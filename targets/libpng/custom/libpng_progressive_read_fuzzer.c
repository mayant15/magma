/* Minimal libFuzzer harness for libpng's progressive reader. */

#include <stddef.h>
#include <stdint.h>

#include "png.h"

static void
info_callback(png_structp png_ptr, png_infop info_ptr)
{
   (void)info_ptr;
   png_start_read_image(png_ptr);
}

static void
row_callback(png_structp png_ptr, png_bytep row, png_uint_32 row_number,
    int pass)
{
   (void)png_ptr;
   (void)row;
   (void)row_number;
   (void)pass;
}

static void
end_callback(png_structp png_ptr, png_infop info_ptr)
{
   (void)png_ptr;
   (void)info_ptr;
}

int
LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
   png_structp png_ptr;
   png_infop info_ptr;

   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
   if (png_ptr == NULL)
      return 0;

   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL)
   {
      png_destroy_read_struct(&png_ptr, NULL, NULL);
      return 0;
   }

   if (setjmp(png_jmpbuf(png_ptr)) == 0)
   {
      png_set_progressive_read_fn(png_ptr, NULL, info_callback, row_callback,
          end_callback);
      png_process_data(png_ptr, info_ptr, (png_bytep)data, size);
   }

   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
   return 0;
}
