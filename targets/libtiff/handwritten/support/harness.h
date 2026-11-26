/* Shared plumbing for the hand-written libtiff harnesses.
 *
 * Each harness defines `static int fuzz_one(const uint8_t *, size_t)`; this
 * header supplies a file-reading main() (AFL `@@` style, like the traffic and
 * ogharn harnesses) plus:
 *
 *  - in-memory TIFFClientOpen I/O: a read-only source over the input, and a
 *    growable sink for harnesses that write a TIFF back out;
 *  - silenced error/warning handlers;
 *  - a per-input configuration word taken from the last 4 bytes of the input.
 *    TIFF is offset-addressed, so trailing bytes are ignored by the parser:
 *    seed files parse unchanged and mutating the tail changes the config.
 *
 * The magma libtiff build has zlib, lzma, jpeg (OJPEG + JPEG), PixarLog,
 * LogLuv, NeXT and LZW (with LZW_COMPAT) codecs. JBIG is only present if
 * libjbig-dev is installed in the build image.
 */

#ifndef LIBTIFF_HANDWRITTEN_HARNESS_H
#define LIBTIFF_HANDWRITTEN_HARNESS_H

#include <tiffio.h>

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Upper bound on any buffer the harness allocates for decoded data. */
#ifndef HARNESS_MAX_BUF
#define HARNESS_MAX_BUF ((tmsize_t)64 << 20)
#endif

/* Caps on work per input (directories, strips/tiles, scanlines). */
#define HARNESS_MAX_DIRS 8
#define HARNESS_MAX_STRILES 256
#define HARNESS_MAX_ROWS 4096

/* ---- configuration ------------------------------------------------------ */

static inline uint32_t harness_config(const uint8_t *data, size_t size) {
  uint32_t raw = 0;
  size_t i, n = size < 4 ? size : 4;
  for (i = 0; i < n; i++)
    raw |= (uint32_t)data[size - n + i] << (8 * i);
  return raw;
}

/* Open-mode suffixes: strip chopping on/off, deferred / lazy strile loading,
 * memory mapping off. 'O' (lazy) lets directories with huge strile counts be
 * opened without materialising the offset arrays. */
static const char *const harness_modes[8] = {
    "r", "rO", "rD", "rc", "rm", "rOc", "rDm", "rCO",
};

/* ---- silence libtiff ---------------------------------------------------- */

static void harness_quiet(const char *module, const char *fmt, va_list ap) {
  (void)module;
  (void)fmt;
  (void)ap;
}

/* Set HARNESS_VERBOSE=1 to see libtiff's diagnostics when triaging. */
static inline void harness_silence(void) {
  if (getenv("HARNESS_VERBOSE") != NULL)
    return;
  TIFFSetErrorHandler(harness_quiet);
  TIFFSetWarningHandler(harness_quiet);
}

/* ---- in-memory I/O ------------------------------------------------------ */

typedef struct {
  uint8_t *data;
  toff_t size;
  toff_t cap;
  toff_t pos;
  int writable;
} harness_io;

static tsize_t harness_read(thandle_t h, tdata_t buf, tsize_t n) {
  harness_io *io = (harness_io *)h;
  toff_t left;
  if (io->pos >= io->size)
    return 0;
  left = io->size - io->pos;
  if ((toff_t)n > left)
    n = (tsize_t)left;
  memcpy(buf, io->data + io->pos, (size_t)n);
  io->pos += (toff_t)n;
  return n;
}

static tsize_t harness_write(thandle_t h, tdata_t buf, tsize_t n) {
  harness_io *io = (harness_io *)h;
  toff_t end;
  if (!io->writable || n < 0)
    return 0;
  end = io->pos + (toff_t)n;
  if (end > (toff_t)HARNESS_MAX_BUF)
    return 0;
  if (end > io->cap) {
    toff_t cap = io->cap ? io->cap : 4096;
    uint8_t *p;
    while (cap < end)
      cap *= 2;
    p = (uint8_t *)realloc(io->data, (size_t)cap);
    if (p == NULL)
      return 0;
    memset(p + io->cap, 0, (size_t)(cap - io->cap));
    io->data = p;
    io->cap = cap;
  }
  memcpy(io->data + io->pos, buf, (size_t)n);
  io->pos = end;
  if (end > io->size)
    io->size = end;
  return n;
}

static toff_t harness_seek(thandle_t h, toff_t off, int whence) {
  harness_io *io = (harness_io *)h;
  toff_t base;
  switch (whence) {
  case SEEK_SET: base = 0; break;
  case SEEK_CUR: base = io->pos; break;
  case SEEK_END: base = io->size; break;
  default: return (toff_t)-1;
  }
  /* toff_t is unsigned; negative offsets wrap, which is what libtiff expects
   * for SEEK_CUR/SEEK_END with a negative delta. */
  io->pos = base + off;
  return io->pos;
}

static int harness_close(thandle_t h) {
  (void)h;
  return 0;
}

static toff_t harness_size(thandle_t h) {
  return ((harness_io *)h)->size;
}

static int harness_map(thandle_t h, tdata_t *base, toff_t *size) {
  harness_io *io = (harness_io *)h;
  if (io->writable)
    return 0;
  *base = io->data;
  *size = io->size;
  return 1;
}

static void harness_unmap(thandle_t h, tdata_t base, toff_t size) {
  (void)h;
  (void)base;
  (void)size;
}

static inline TIFF *harness_open_read(harness_io *io, const uint8_t *data,
                                      size_t size, const char *mode) {
  memset(io, 0, sizeof *io);
  io->data = (uint8_t *)data;
  io->size = (toff_t)size;
  return TIFFClientOpen("input", mode, (thandle_t)io, harness_read,
                        harness_write, harness_seek, harness_close,
                        harness_size, harness_map, harness_unmap);
}

static inline TIFF *harness_open_write(harness_io *io, const char *mode) {
  memset(io, 0, sizeof *io);
  io->writable = 1;
  return TIFFClientOpen("output", mode, (thandle_t)io, harness_read,
                        harness_write, harness_seek, harness_close,
                        harness_size, harness_map, harness_unmap);
}

static inline void harness_io_free(harness_io *io) {
  if (io->writable)
    free(io->data);
  memset(io, 0, sizeof *io);
}

/* A stream for TIFFPrintDirectory that discards everything. */
static inline FILE *harness_null_stream(void) {
  static FILE *f;
  if (f == NULL)
    f = fopen("/dev/null", "w");
  return f;
}

/* ---- main --------------------------------------------------------------- */

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

  harness_silence();
  ret = fuzz_one(buf, (size_t)size);
  free(buf);
  return ret;
}

#endif /* LIBTIFF_HANDWRITTEN_HARNESS_H */
