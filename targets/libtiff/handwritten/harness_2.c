/* API-sequence driver: run a short program of libtiff calls on one handle.
 *
 * Input layout:  <TIFF bytes> <op 0> ... <op n-1> <n>
 *   The last byte is the op count n (capped at MAX_OPS); each op is 4 bytes
 *   {code, a, b, c} directly before it. The whole input is handed to libtiff
 *   (the trailer is ignored by the parser, TIFF being offset-addressed).
 *
 * Ops (code % NUM_OPS):
 *   0 TIFFReadScanline(row = a | b << 8, sample = c & 3)
 *   1 TIFFReadEncodedStrip(a, size = b << 8 | c, 0 = whole)
 *   2 TIFFReadEncodedTile(a, size = b << 8 | c, 0 = whole)
 *   3 TIFFSetField(Compression, codecs[a]): reinterpret the current data
 *   4 TIFFSetField on a field from fields[a] with value b | c << 8
 *   5 TIFFReadDirectory
 *   6 TIFFSetDirectory(a)
 *   7 TIFFPrintDirectory(flags a)
 *   8 TIFFReadRGBAStrip / TIFFReadRGBATile(row = a | b << 8)
 *
 *   TIF003  RowsPerStrip changed on a handle with ImageLength 0xffffffff:
 *           the strip count was computed with the overflow-checked
 *           TIFFhowmany_32 at directory read time, the strip size is not
 *   TIF004  OJPEG codec installed on a handle mid-strip: OJPEGDecode runs
 *           without OJPEGPreDecode ever succeeding (decoder_ok == 0)
 *   TIF001, TIF002, TIF008, TIF010, TIF011, TIF012 are also reachable
 *   (TIF012 directly: SamplesPerPixel changed with SMinSampleValue set).
 */

#include "harness.h"

#define MAX_OPS 32
#define NUM_OPS 9

static const uint16_t codecs[16] = {
    COMPRESSION_NONE,     COMPRESSION_CCITTRLE, COMPRESSION_CCITTFAX3,
    COMPRESSION_CCITTFAX4, COMPRESSION_LZW,     COMPRESSION_OJPEG,
    COMPRESSION_JPEG,     COMPRESSION_NEXT,     COMPRESSION_PACKBITS,
    COMPRESSION_THUNDERSCAN, COMPRESSION_PIXARLOG, COMPRESSION_DEFLATE,
    COMPRESSION_SGILOG,   COMPRESSION_SGILOG24, COMPRESSION_LZMA,
    COMPRESSION_JBIG,
};

#define NUM_FIELDS 10
static const uint32_t fields[NUM_FIELDS] = {
    TIFFTAG_SAMPLESPERPIXEL, TIFFTAG_EXTRASAMPLES,  TIFFTAG_PHOTOMETRIC,
    TIFFTAG_PREDICTOR,       TIFFTAG_JPEGCOLORMODE, TIFFTAG_PIXARLOGDATAFMT,
    TIFFTAG_SGILOGDATAFMT,   TIFFTAG_PLANARCONFIG,  TIFFTAG_ROWSPERSTRIP,
    TIFFTAG_BITSPERSAMPLE,
};

static void set_field(TIFF *tif, uint32_t tag, unsigned v) {
  if (tag == TIFFTAG_EXTRASAMPLES) {
    uint16_t info[8] = {0};
    TIFFSetField(tif, tag, (uint16_t)(v & 7), info);
  } else if (tag == TIFFTAG_ROWSPERSTRIP) {
    TIFFSetField(tif, tag, (uint32_t)v);
  } else {
    TIFFSetField(tif, tag, (int)(uint16_t)v);
  }
}

static void op_read_strile(TIFF *tif, int tile, uint32_t idx, tmsize_t want) {
  tmsize_t sz = tile ? TIFFTileSize(tif) : TIFFStripSize(tif);
  void *buf;
  if (sz <= 0 || sz > HARNESS_MAX_BUF)
    return;
  buf = _TIFFmalloc(sz);
  if (buf == NULL)
    return;
  if (want <= 0 || want > sz)
    want = (tmsize_t)-1;
  if (tile)
    TIFFReadEncodedTile(tif, idx, buf, want);
  else
    TIFFReadEncodedStrip(tif, idx, buf, want);
  _TIFFfree(buf);
}

static void op_read_rgba(TIFF *tif, uint32_t row) {
  uint32_t w = 0, h = 0, bw, bh;
  uint32_t *raster;
  char emsg[1024];
  int tiled = TIFFIsTiled(tif);

  TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &w);
  if (tiled) {
    TIFFGetField(tif, TIFFTAG_TILEWIDTH, &bw);
    TIFFGetField(tif, TIFFTAG_TILELENGTH, &bh);
  } else {
    bw = w;
    TIFFGetFieldDefaulted(tif, TIFFTAG_ROWSPERSTRIP, &bh);
    TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &h);
    if (bh > h)
      bh = h;
  }
  if (bw == 0 || bh == 0 || (uint64_t)bw * bh > (uint64_t)HARNESS_MAX_BUF / 4)
    return;
  if (!TIFFRGBAImageOK(tif, emsg))
    return;
  raster = (uint32_t *)_TIFFmalloc((tmsize_t)bw * bh * 4);
  if (raster == NULL)
    return;
  if (tiled)
    TIFFReadRGBATile(tif, 0, row - row % bh, raster);
  else
    TIFFReadRGBAStrip(tif, row - row % bh, raster);
  _TIFFfree(raster);
}

static void op_read_scanline(TIFF *tif, uint32_t row, uint16_t sample) {
  tmsize_t sz = TIFFScanlineSize(tif);
  void *buf;
  if (sz <= 0 || sz > HARNESS_MAX_BUF)
    return;
  buf = _TIFFmalloc(sz);
  if (buf == NULL)
    return;
  TIFFReadScanline(tif, buf, row, sample);
  _TIFFfree(buf);
}

static int fuzz_one(const uint8_t *data, size_t size) {
  harness_io io;
  TIFF *tif;
  size_t nops, i;
  const uint8_t *ops;

  if (size < 1)
    return 0;
  nops = data[size - 1];
  if (nops > MAX_OPS)
    nops = MAX_OPS;
  if (size < 1 + 4 * nops)
    nops = (size - 1) / 4;
  ops = data + size - 1 - 4 * nops;

  tif = harness_open_read(&io, data, size, "r");
  if (tif == NULL)
    return 0;

  for (i = 0; i < nops; i++) {
    const uint8_t *op = ops + 4 * i;
    unsigned a = op[1], b = op[2], c = op[3];

    switch (op[0] % NUM_OPS) {
    case 0:
      op_read_scanline(tif, a | b << 8, (uint16_t)(c & 3));
      break;
    case 1:
      op_read_strile(tif, 0, a, (tmsize_t)(b << 8 | c));
      break;
    case 2:
      op_read_strile(tif, 1, a, (tmsize_t)(b << 8 | c));
      break;
    case 3:
      TIFFSetField(tif, TIFFTAG_COMPRESSION, codecs[a % 16]);
      break;
    case 4:
      set_field(tif, fields[a % NUM_FIELDS], b | c << 8);
      break;
    case 5:
      TIFFReadDirectory(tif);
      break;
    case 6:
      TIFFSetDirectory(tif, (uint16_t)a);
      break;
    case 7:
      TIFFPrintDirectory(tif, harness_null_stream(), (long)a);
      break;
    case 8:
      op_read_rgba(tif, a | b << 8);
      break;
    }
  }

  TIFFClose(tif);
  return 0;
}
