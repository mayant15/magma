#ifndef _TRAFFIC_LIBTIFF_SUPPORT_H
#define _TRAFFIC_LIBTIFF_SUPPORT_H

#include <tiffio.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  uint8_t* data;
  size_t size;
  size_t offset;
} test_input_t;

static tmsize_t traffic_tiff_read(thandle_t handle, void* buffer,
                                  tmsize_t requested) {
  test_input_t* input = (test_input_t*)handle;
  size_t available;
  size_t count;

  if (requested <= 0 || input->offset >= input->size)
    return 0;

  available = input->size - input->offset;
  count = (uint64_t)requested < (uint64_t)available
              ? (size_t)requested
              : available;
  memcpy(buffer, input->data + input->offset, count);
  input->offset += count;
  return (tmsize_t)count;
}

static tmsize_t traffic_tiff_write(thandle_t handle, void* buffer,
                                   tmsize_t size) {
  (void)handle;
  (void)buffer;
  (void)size;
  return 0;
}

static toff_t traffic_tiff_seek(thandle_t handle, toff_t offset, int whence) {
  test_input_t* input = (test_input_t*)handle;
  size_t base;

  switch (whence) {
    case SEEK_SET:
      base = 0;
      break;
    case SEEK_CUR:
      base = input->offset;
      break;
    case SEEK_END:
      base = input->size;
      break;
    default:
      return (toff_t)-1;
  }

  if (offset > (toff_t)(input->size - base))
    return (toff_t)-1;

  input->offset = base + (size_t)offset;
  return (toff_t)input->offset;
}

static int traffic_tiff_close(thandle_t handle) {
  return 0;
}

static toff_t traffic_tiff_size(thandle_t handle) {
  test_input_t* input = (test_input_t*)handle;
  return (toff_t)input->size;
}

TIFF* tiff_client_open(uint8_t* data, size_t size, test_input_t* input) {
  if (data == NULL && size != 0)
    return NULL;

  input->data = data;
  input->size = size;
  input->offset = 0;

  return TIFFClientOpen("fuzzer-input.tiff", "r", (thandle_t)input,
                        traffic_tiff_read, traffic_tiff_write,
                        traffic_tiff_seek, traffic_tiff_close,
                        traffic_tiff_size, NULL, NULL);
}

// Status-style wrappers so Traffic can model failure without NULL: the
// generator cannot construct NULL, and a NULL-able (ptr TIFF) return cannot
// carry ghost facts about the handle. Each wrapper returns 0 on success.
static int tiff_fuzz_client_open(uint8_t* data, size_t size,
                                 test_input_t* input, TIFF** out) {
  TIFF* tif = tiff_client_open(data, size, input);
  if (tif == NULL)
    return 1;
  *out = tif;
  return 0;
}

// Decode entry points write into a caller-allocated buffer whose size comes
// from the parsed directory. Traffic has no sized-buffer allocation, so these
// wrappers allocate internally; the harness only observes the status int.
static int tiff_fuzz_read_scanline(TIFF* tif, uint32_t row, uint16_t sample) {
  tmsize_t size = TIFFScanlineSize(tif);
  void* buf;
  int status;

  if (size <= 0)
    return 1;
  buf = malloc((size_t)size);
  if (buf == NULL)
    return 1;
  status = TIFFReadScanline(tif, buf, row, sample);
  free(buf);
  return status == 0 ? 1 : 0;
}

static int tiff_fuzz_read_encoded_strip(TIFF* tif, uint32_t strip) {
  tmsize_t size = TIFFStripSize(tif);
  void* buf;
  int status;

  if (size <= 0)
    return 1;
  buf = malloc((size_t)size);
  if (buf == NULL)
    return 1;
  status = TIFFReadEncodedStrip(tif, strip, buf, size);
  free(buf);
  return status < 0 ? 1 : 0;
}

static int tiff_fuzz_read_encoded_tile(TIFF* tif, uint32_t tile) {
  tmsize_t size = TIFFTileSize(tif);
  void* buf;
  int status;

  if (size <= 0)
    return 1;
  buf = malloc((size_t)size);
  if (buf == NULL)
    return 1;
  status = TIFFReadEncodedTile(tif, tile, buf, size);
  free(buf);
  return status < 0 ? 1 : 0;
}

static int tiff_fuzz_read_rgba(TIFF* tif) {
  uint32_t w;
  uint32_t h;
  uint32_t* raster;
  int status;

  if (TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w) != 1)
    return 1;
  if (TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h) != 1)
    return 1;
  if (w == 0 || h == 0 || w > 0x1000 || h > 0x1000)
    return 1;
  raster = (uint32_t*)malloc((size_t)w * (size_t)h * sizeof(uint32_t));
  if (raster == NULL)
    return 1;
  status = TIFFReadRGBAImage(tif, w, h, raster, 0);
  free(raster);
  return status == 0 ? 1 : 0;
}

#endif // _TRAFFIC_LIBTIFF_SUPPORT_H
