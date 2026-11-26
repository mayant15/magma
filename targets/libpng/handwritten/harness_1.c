/* Progressive (push) reader at the image's native pixel format.
 *
 * No widening transforms, so sub-byte (1/2/4-bit) images keep
 * max_pixel_depth < 8 in png_read_start_row; interlace handling routes rows
 * through png_progressive_combine_row -> png_combine_row(display = 1).
 * Input is pushed in small pieces to exercise pngpread's buffering.
 *
 *   PNG001  IDAT header -> png_check_chunk_length (pngpread.c)
 *   PNG003  PLTE with more entries than 1 << bit_depth
 *   PNG004  reached via png_combine_row on odd Adam7 passes
 *   PNG005  sub-byte image: row_bytes < aligned width in png_read_start_row
 *   PNG006  eXIf chunk cut short by EOF, then png_destroy_read_struct
 */

#include "harness.h"

#define PUSH_CHUNK 509 /* odd size so chunk boundaries move around */

static struct {
  png_structp png;
  png_infop info;
  png_bytep row;
} ctx;

static void cleanup(void) {
  free(ctx.row);
  ctx.row = NULL;
  png_destroy_read_struct(&ctx.png, &ctx.info, NULL);
}

static void info_cb(png_structp png, png_infop info) {
  if (png_get_rowbytes(png, info) > HARNESS_MAX_INPUT_ROW)
    png_error(png, "row too large for harness");

  (void)png_set_interlace_handling(png);
  png_read_update_info(png, info);

  ctx.row = (png_bytep)calloc(1, png_get_rowbytes(png, info));
  if (ctx.row == NULL)
    png_error(png, "harness row allocation failed");
}

static void row_cb(png_structp png, png_bytep new_row, png_uint_32 row_num,
                   int pass) {
  (void)row_num;
  (void)pass;
  if (new_row != NULL && ctx.row != NULL)
    png_progressive_combine_row(png, ctx.row, new_row);
}

static void end_cb(png_structp png, png_infop info) {
  (void)png;
  (void)info;
}

static int fuzz_one(const uint8_t *data, size_t size) {
  size_t off, n;

  if (size < 8 || png_sig_cmp(data, 0, 8) != 0)
    return 0;

  memset(&ctx, 0, sizeof ctx);
  ctx.png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (ctx.png == NULL)
    return 0;
  ctx.info = png_create_info_struct(ctx.png);
  if (ctx.info == NULL) {
    cleanup();
    return 0;
  }

  if (setjmp(png_jmpbuf(ctx.png))) {
    cleanup();
    return 0;
  }

  harness_setup_png(ctx.png);
  png_set_progressive_read_fn(ctx.png, NULL, info_cb, row_cb, end_cb);

  for (off = 0; off < size; off += n) {
    n = size - off < PUSH_CHUNK ? size - off : PUSH_CHUNK;
    png_process_data(ctx.png, ctx.info, (png_bytep)(data + off), n);
  }

  cleanup();
  return 0;
}
