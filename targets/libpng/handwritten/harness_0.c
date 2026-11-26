/* Sequential (pull) reader with every widening transform enabled.
 *
 * png_set_expand + gray_to_rgb + filler + expand_16 turn every input format
 * into 64-bit RGBA, and png_set_interlace_handling makes libpng expand Adam7
 * passes through png_combine_row's masked path.
 *
 *   PNG001  IDAT header -> png_check_chunk_length (RGB8, width 0x55555555)
 *   PNG003  PLTE with more entries than 1 << bit_depth
 *   PNG004  interlaced image, width > 2^29: width * 8 overflows png_uint_32
 *   PNG005  reached in png_read_start_row (triggered by harness_1)
 *   PNG006  eXIf chunk truncated mid-read, then png_destroy_read_struct
 *   PNG007  palette image with a zero-length PLTE + png_set_expand
 */

#include "harness.h"

static struct {
  png_structp png;
  png_infop info;
  png_infop end;
  png_bytep row;
} ctx;

static void cleanup(void) {
  free(ctx.row);
  ctx.row = NULL;
  png_destroy_read_struct(&ctx.png, &ctx.info, &ctx.end);
}

static int fuzz_one(const uint8_t *data, size_t size) {
  harness_src src;
  png_uint_32 height, y;
  int passes, pass;

  if (size < 8 || png_sig_cmp(data, 0, 8) != 0)
    return 0;

  memset(&ctx, 0, sizeof ctx);
  ctx.png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (ctx.png == NULL)
    return 0;
  ctx.info = png_create_info_struct(ctx.png);
  ctx.end = png_create_info_struct(ctx.png);
  if (ctx.info == NULL || ctx.end == NULL) {
    cleanup();
    return 0;
  }

  if (setjmp(png_jmpbuf(ctx.png))) {
    cleanup();
    return 0;
  }

  harness_setup_png(ctx.png);
  src.data = data;
  src.left = size;
  png_set_read_fn(ctx.png, &src, harness_read_fn);

  png_read_info(ctx.png, ctx.info);

  if (png_get_rowbytes(ctx.png, ctx.info) > HARNESS_MAX_INPUT_ROW) {
    cleanup();
    return 0;
  }

  png_set_expand(ctx.png);
  png_set_gray_to_rgb(ctx.png);
  png_set_filler(ctx.png, 0xffff, PNG_FILLER_AFTER);
  png_set_expand_16(ctx.png);
  passes = png_set_interlace_handling(ctx.png);

  png_read_update_info(ctx.png, ctx.info);

  /* Plain malloc: the full transformed row can be ~4 GiB for PNG004, but only
   * the pages png_combine_row actually writes get touched. */
  ctx.row = (png_bytep)malloc(png_get_rowbytes(ctx.png, ctx.info));
  if (ctx.row == NULL) {
    cleanup();
    return 0;
  }

  height = png_get_image_height(ctx.png, ctx.info);
  for (pass = 0; pass < passes; pass++)
    for (y = 0; y < height; y++)
      png_read_row(ctx.png, ctx.row, NULL);

  png_read_end(ctx.png, ctx.end);

  cleanup();
  return 0;
}
