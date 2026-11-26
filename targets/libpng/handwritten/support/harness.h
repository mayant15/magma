/* Shared plumbing for the hand-written libpng harnesses.
 *
 * Each harness defines `static int fuzz_one(const uint8_t *, size_t)`; this
 * header supplies a file-reading main() (AFL `@@` style, matching the traffic
 * and ogharn harnesses) plus in-memory I/O and allocation helpers.
 *
 * The magma libpng build has STDIO and WRITE disabled, and user width/height
 * limits raised to 0x7fffffff (see patches/setup/libpng16.patch).
 */

#ifndef LIBPNG_HANDWRITTEN_HARNESS_H
#define LIBPNG_HANDWRITTEN_HARNESS_H

#include <png.h>

#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Largest single allocation libpng may make. PNG004 needs a ~4 GiB row buffer
 * (width * 8 bytes/pixel >= 2^32), so the cap sits just above that. Anything
 * larger is refused (libpng raises "Out of memory" and we bail cleanly). */
#ifndef HARNESS_MAX_ALLOC
#define HARNESS_MAX_ALLOC (((size_t)1 << 32) + ((size_t)1 << 24))
#endif

/* Largest *untransformed* row we accept. libpng memsets prev_row (this size)
 * in png_read_start_row, so this bounds real memory touched per input. */
#ifndef HARNESS_MAX_INPUT_ROW
#define HARNESS_MAX_INPUT_ROW ((size_t)256 << 20)
#endif

typedef struct {
  const uint8_t *data;
  size_t left;
} harness_src;

static inline void harness_read_fn(png_structp png, png_bytep out, size_t len) {
  harness_src *src = (harness_src *)png_get_io_ptr(png);
  if (len > src->left)
    png_error(png, "read past end of input");
  memcpy(out, src->data, len);
  src->data += len;
  src->left -= len;
}

static inline png_voidp harness_malloc(png_structp png, png_alloc_size_t size) {
  (void)png;
  if (size > HARNESS_MAX_ALLOC)
    return NULL;
  return malloc(size);
}

static inline void harness_free(png_structp png, png_voidp ptr) {
  (void)png;
  free(ptr);
}

/* Options common to the low-level (png_struct) harnesses: bounded allocator,
 * and ignore CRC / Adler-32 errors so mutated headers are not rejected before
 * they reach interesting code (IHDR width/depth, PLTE length, etc.). */
static inline void harness_setup_png(png_structp png) {
  png_set_mem_fn(png, NULL, harness_malloc, harness_free);
  png_set_crc_action(png, PNG_CRC_QUIET_USE, PNG_CRC_QUIET_USE);
#if defined(PNG_SET_OPTION_SUPPORTED) && defined(PNG_IGNORE_ADLER32)
  png_set_option(png, PNG_IGNORE_ADLER32, PNG_OPTION_ON);
#endif
}

static int fuzz_one(const uint8_t *data, size_t size);

int main(int argc, char *argv[]) {
  FILE *f;
  long size;
  uint8_t *buf;
  int ret;

  if (argc < 2)
    return 0;

  f = fopen(argv[1], "rb");
  if (f == NULL)
    return 0;

  fseek(f, 0, SEEK_END);
  size = ftell(f);
  rewind(f);
  if (size < 1) {
    fclose(f);
    return 0;
  }

  buf = (uint8_t *)malloc((size_t)size);
  if (buf == NULL || fread(buf, (size_t)size, 1, f) != 1) {
    fclose(f);
    free(buf);
    return 0;
  }
  fclose(f);

  ret = fuzz_one(buf, (size_t)size);
  free(buf);
  return ret;
}

#endif /* LIBPNG_HANDWRITTEN_HARNESS_H */
