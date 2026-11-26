/* Converter: re-encode the first image into an in-memory TIFF (tiffcp-like).
 *
 * Tags are copied in tiffcp's order (geometry, compression, photometric,
 * layout, TransferFunction/ColorMap, then the remaining tags), the pixels are
 * copied scanline by scanline, and TIFFClose flushes the output directory.
 *
 * Configuration (last 4 bytes of the input, see harness.h):
 *   bits 0-2   output compression (none, LZW, deflate, PackBits, SGILog,
 *              SGILog24, PixarLog, LZMA)
 *   bits 4-5   predictor: 0/3 none, 1 horizontal, 2 floating point
 *   bit  6     drop ExtraSamples (flatten alpha / extra channels)
 *   bits 8-15  output RowsPerStrip (0 = TIFFDefaultStripSize)
 *   bit  16    write BigTIFF
 *
 *   TIF001  predictor encode with a row that is not a multiple of the stride
 *   TIF005  SGILog output whose encoder was never (successfully) set up
 *   TIF006  PixarLog output whose encoder was never (successfully) set up
 *   TIF009  ExtraSamples dropped: 1-table TransferFunction, 2+ colour samples
 */

#include "harness.h"

static const uint16_t out_compression[8] = {
    COMPRESSION_NONE,   COMPRESSION_LZW,     COMPRESSION_ADOBE_DEFLATE,
    COMPRESSION_PACKBITS, COMPRESSION_SGILOG, COMPRESSION_SGILOG24,
    COMPRESSION_PIXARLOG, COMPRESSION_LZMA,
};

#define COPY_U16(tag)                                                         \
  do {                                                                         \
    uint16_t v_;                                                               \
    if (TIFFGetField(in, tag, &v_))                                            \
      TIFFSetField(out, tag, v_);                                              \
  } while (0)

#define COPY_U32(tag)                                                         \
  do {                                                                         \
    uint32_t v_;                                                               \
    if (TIFFGetField(in, tag, &v_))                                            \
      TIFFSetField(out, tag, v_);                                              \
  } while (0)

#define COPY_U16_PAIR(tag)                                                    \
  do {                                                                         \
    uint16_t a_, b_;                                                           \
    if (TIFFGetField(in, tag, &a_, &b_))                                       \
      TIFFSetField(out, tag, a_, b_);                                          \
  } while (0)

#define COPY_FLOAT(tag)                                                       \
  do {                                                                         \
    float v_;                                                                  \
    if (TIFFGetField(in, tag, &v_))                                            \
      TIFFSetField(out, tag, v_);                                              \
  } while (0)

#define COPY_DOUBLE(tag)                                                      \
  do {                                                                         \
    double v_;                                                                 \
    if (TIFFGetField(in, tag, &v_))                                            \
      TIFFSetField(out, tag, v_);                                              \
  } while (0)

#define COPY_STRING(tag)                                                      \
  do {                                                                         \
    char *v_;                                                                  \
    if (TIFFGetField(in, tag, &v_))                                            \
      TIFFSetField(out, tag, v_);                                              \
  } while (0)

#define COPY_FLOAT_ARRAY(tag)                                                 \
  do {                                                                         \
    float *v_;                                                                 \
    if (TIFFGetField(in, tag, &v_))                                            \
      TIFFSetField(out, tag, v_);                                              \
  } while (0)

static void copy_tags(TIFF *in, TIFF *out, uint32_t cfg) {
  uint32_t w = 0, h = 0;
  uint16_t bps = 1, spp = 1, planar = PLANARCONFIG_CONTIG, pred;
  uint16_t *a, *b, *c;
  uint32_t rps = (cfg >> 8) & 0xff;

  TIFFGetField(in, TIFFTAG_IMAGEWIDTH, &w);
  TIFFGetField(in, TIFFTAG_IMAGELENGTH, &h);
  TIFFGetFieldDefaulted(in, TIFFTAG_BITSPERSAMPLE, &bps);
  TIFFGetFieldDefaulted(in, TIFFTAG_SAMPLESPERPIXEL, &spp);
  TIFFGetFieldDefaulted(in, TIFFTAG_PLANARCONFIG, &planar);

  TIFFSetField(out, TIFFTAG_IMAGEWIDTH, w);
  TIFFSetField(out, TIFFTAG_IMAGELENGTH, h);
  TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, bps);
  TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, spp);
  TIFFSetField(out, TIFFTAG_COMPRESSION, out_compression[cfg & 7]);
  COPY_U16(TIFFTAG_PHOTOMETRIC);
  COPY_U16(TIFFTAG_FILLORDER);
  COPY_U16(TIFFTAG_ORIENTATION);

  pred = (cfg >> 4) & 3;
  if (pred == 1 || pred == 2)
    TIFFSetField(out, TIFFTAG_PREDICTOR,
                 pred == 1 ? PREDICTOR_HORIZONTAL : PREDICTOR_FLOATINGPOINT);

  TIFFSetField(out, TIFFTAG_ROWSPERSTRIP,
               rps ? rps : TIFFDefaultStripSize(out, 0));
  TIFFSetField(out, TIFFTAG_PLANARCONFIG, planar);

  /* TransferFunction and ColorMap: three pointers, the last two NULL when the
   * input has a single colour channel. */
  a = b = c = NULL;
  if (TIFFGetField(in, TIFFTAG_TRANSFERFUNCTION, &a, &b, &c))
    TIFFSetField(out, TIFFTAG_TRANSFERFUNCTION, a, b, c);
  a = b = c = NULL;
  if (TIFFGetField(in, TIFFTAG_COLORMAP, &a, &b, &c))
    TIFFSetField(out, TIFFTAG_COLORMAP, a, b, c);

  COPY_U32(TIFFTAG_SUBFILETYPE);
  COPY_U16(TIFFTAG_THRESHHOLDING);
  COPY_STRING(TIFFTAG_DOCUMENTNAME);
  COPY_STRING(TIFFTAG_IMAGEDESCRIPTION);
  COPY_STRING(TIFFTAG_MAKE);
  COPY_STRING(TIFFTAG_MODEL);
  COPY_U16(TIFFTAG_MINSAMPLEVALUE);
  COPY_U16(TIFFTAG_MAXSAMPLEVALUE);
  COPY_FLOAT(TIFFTAG_XRESOLUTION);
  COPY_FLOAT(TIFFTAG_YRESOLUTION);
  COPY_STRING(TIFFTAG_PAGENAME);
  COPY_FLOAT(TIFFTAG_XPOSITION);
  COPY_FLOAT(TIFFTAG_YPOSITION);
  COPY_U16(TIFFTAG_RESOLUTIONUNIT);
  COPY_STRING(TIFFTAG_SOFTWARE);
  COPY_STRING(TIFFTAG_DATETIME);
  COPY_STRING(TIFFTAG_ARTIST);
  COPY_STRING(TIFFTAG_HOSTCOMPUTER);
  COPY_FLOAT_ARRAY(TIFFTAG_WHITEPOINT);
  COPY_FLOAT_ARRAY(TIFFTAG_PRIMARYCHROMATICITIES);
  COPY_U16_PAIR(TIFFTAG_HALFTONEHINTS);
  COPY_U16(TIFFTAG_INKSET);
  COPY_U16_PAIR(TIFFTAG_DOTRANGE);
  COPY_STRING(TIFFTAG_TARGETPRINTER);
  COPY_U16(TIFFTAG_SAMPLEFORMAT);
  COPY_FLOAT_ARRAY(TIFFTAG_YCBCRCOEFFICIENTS);
  COPY_U16_PAIR(TIFFTAG_YCBCRSUBSAMPLING);
  COPY_U16(TIFFTAG_YCBCRPOSITIONING);
  COPY_FLOAT_ARRAY(TIFFTAG_REFERENCEBLACKWHITE);
  if (!(cfg & 0x40)) {
    uint16_t n, *info;
    if (TIFFGetField(in, TIFFTAG_EXTRASAMPLES, &n, &info))
      TIFFSetField(out, TIFFTAG_EXTRASAMPLES, n, info);
  }
  COPY_DOUBLE(TIFFTAG_SMINSAMPLEVALUE);
  COPY_DOUBLE(TIFFTAG_SMAXSAMPLEVALUE);
  COPY_DOUBLE(TIFFTAG_STONITS);
}

static void copy_pixels(TIFF *in, TIFF *out) {
  uint32_t h = 0, row, nrows;
  uint16_t planar = PLANARCONFIG_CONTIG, spp = 1, s, nsamples;
  tmsize_t in_sz = TIFFScanlineSize(in), out_sz = TIFFScanlineSize(out);
  tmsize_t sz = in_sz > out_sz ? in_sz : out_sz;
  void *buf;

  if (TIFFIsTiled(in) || in_sz <= 0 || out_sz <= 0 || sz > HARNESS_MAX_BUF)
    return;
  TIFFGetField(in, TIFFTAG_IMAGELENGTH, &h);
  TIFFGetFieldDefaulted(in, TIFFTAG_PLANARCONFIG, &planar);
  TIFFGetFieldDefaulted(in, TIFFTAG_SAMPLESPERPIXEL, &spp);
  nsamples = planar == PLANARCONFIG_SEPARATE ? spp : 1;
  nrows = h < HARNESS_MAX_ROWS ? h : HARNESS_MAX_ROWS;

  buf = _TIFFmalloc(sz);
  if (buf == NULL)
    return;
  memset(buf, 0, (size_t)sz);
  for (s = 0; s < nsamples && s < 4; s++)
    for (row = 0; row < nrows; row++) {
      if (TIFFReadScanline(in, buf, row, s) < 0)
        goto out;
      if (TIFFWriteScanline(out, buf, row, s) < 0)
        goto out;
    }
out:
  _TIFFfree(buf);
}

static int fuzz_one(const uint8_t *data, size_t size) {
  uint32_t cfg = harness_config(data, size);
  harness_io in_io, out_io;
  TIFF *in, *out;

  in = harness_open_read(&in_io, data, size, "r");
  if (in == NULL)
    return 0;

  out = harness_open_write(&out_io, (cfg & 0x10000) ? "w8" : "w");
  if (out == NULL) {
    TIFFClose(in);
    return 0;
  }

  copy_tags(in, out, cfg);
  copy_pixels(in, out);

  TIFFClose(out);
  TIFFClose(in);
  harness_io_free(&out_io);
  return 0;
}
