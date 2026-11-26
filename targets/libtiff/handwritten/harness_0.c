/* Reader: walk every directory and decode its image data.
 *
 * Configuration (last 4 bytes of the input, see harness.h):
 *   bits 0-2   open mode (strip chopping, deferred / lazy strile loading, mmap)
 *   bit  3     TIFFPrintDirectory with curves, colormap and strile info
 *   bits 4-5   access: 0 scanlines, 1 whole striles, 2 partial striles, 3 RGBA
 *   bits 8-23  byte count for partial strile reads (1 .. 65536)
 *
 * Scanline reads carry on past decode errors (up to a few per directory), as
 * viewers that render whatever they can do.
 *
 *   TIF001  partial strile read: occ not a multiple of the predictor row size
 *   TIF002  PixarLog tile larger than the image: tile bytes > tbuf_size
 *   TIF007  single uncompressed strip whose byte count exceeds the image
 *   TIF008  NeXT tile wider than the image: runs overrun the image scanline
 *   TIF010  old-style LZW: row decoded after a failed row reuses stale state
 *   TIF011  TIFFPrintDirectory, TransferFunction with ExtraSamples
 *   TIF012  OJPEG with no SamplesPerPixel, SMinSampleValue set (dirread)
 *   TIF013  JBIG partial strile read (only if libtiff is built with JBIG)
 *   TIF014  chopped strip count > 1000000 beyond end of file
 */

#include "harness.h"

#define MAX_ROW_ERRORS 8

static void read_scanlines(TIFF *tif) {
  uint32_t h = 0, row, nrows;
  uint16_t planar = PLANARCONFIG_CONTIG, spp = 1, s, nsamples;
  tmsize_t sz = TIFFScanlineSize(tif);
  unsigned errors = 0;
  void *buf;

  if (sz <= 0 || sz > HARNESS_MAX_BUF)
    return;
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
  TIFFGetField(tif, TIFFTAG_PLANARCONFIG, &planar);
  TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &spp);
  nsamples = planar == PLANARCONFIG_SEPARATE ? spp : 1;
  nrows = h < HARNESS_MAX_ROWS ? h : HARNESS_MAX_ROWS;

  buf = _TIFFmalloc(sz);
  if (buf == NULL)
    return;
  for (s = 0; s < nsamples && s < 4; s++)
    for (row = 0; row < nrows; row++)
      if (TIFFReadScanline(tif, buf, row, s) < 0 && ++errors > MAX_ROW_ERRORS)
        goto out;
out:
  _TIFFfree(buf);
}

static void read_striles(TIFF *tif, int partial, tmsize_t part) {
  int tiled = TIFFIsTiled(tif);
  uint32_t n = tiled ? TIFFNumberOfTiles(tif) : TIFFNumberOfStrips(tif);
  tmsize_t sz = tiled ? TIFFTileSize(tif) : TIFFStripSize(tif);
  tmsize_t want;
  uint32_t i;
  void *buf;

  if (sz <= 0 || sz > HARNESS_MAX_BUF)
    return;
  want = partial && part < sz ? part : (tmsize_t)-1;
  buf = _TIFFmalloc(sz);
  if (buf == NULL)
    return;
  for (i = 0; i < n && i < HARNESS_MAX_STRILES; i++) {
    if (tiled)
      TIFFReadEncodedTile(tif, i, buf, want);
    else
      TIFFReadEncodedStrip(tif, i, buf, want);
  }
  _TIFFfree(buf);
}

static void read_rgba(TIFF *tif) {
  uint32_t w = 0, h = 0;
  uint32_t *raster;
  char emsg[1024];

  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
  TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
  if (w == 0 || h == 0 || (uint64_t)w * h > (uint64_t)HARNESS_MAX_BUF / 4)
    return;
  if (!TIFFRGBAImageOK(tif, emsg))
    return;
  raster = (uint32_t *)_TIFFmalloc((tmsize_t)w * h * 4);
  if (raster == NULL)
    return;
  TIFFReadRGBAImage(tif, w, h, raster, 0);
  _TIFFfree(raster);
}

static int fuzz_one(const uint8_t *data, size_t size) {
  uint32_t cfg = harness_config(data, size);
  int access = (cfg >> 4) & 3;
  tmsize_t part = 1 + (tmsize_t)((cfg >> 8) & 0xffff);
  harness_io io;
  TIFF *tif;
  int dirs = 0;

  tif = harness_open_read(&io, data, size, harness_modes[cfg & 7]);
  if (tif == NULL)
    return 0;

  do {
    if (cfg & 8)
      TIFFPrintDirectory(tif, harness_null_stream(),
                         TIFFPRINT_STRIPS | TIFFPRINT_CURVES |
                             TIFFPRINT_COLORMAP | TIFFPRINT_JPEGQTABLES |
                             TIFFPRINT_JPEGACTABLES);

    switch (access) {
    case 0:
      if (!TIFFIsTiled(tif)) {
        read_scanlines(tif);
        break;
      }
      /* fall through: tiled images have no scanline interface */
    case 1:
      read_striles(tif, 0, 0);
      break;
    case 2:
      read_striles(tif, 1, part);
      break;
    case 3:
      read_rgba(tif);
      break;
    }
  } while (++dirs < HARNESS_MAX_DIRS && TIFFReadDirectory(tif));

  TIFFClose(tif);
  return 0;
}
