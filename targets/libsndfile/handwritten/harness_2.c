/* Transcoder: decode the input (format auto-detected) and re-encode it to a
 * second, fuzzer-chosen format, carrying over every piece of metadata the
 * reader found — strings, instrument / loops, cues, broadcast and cart
 * chunks, channel map — as an application such as sndfile-convert would.
 *
 * The output format comes from the trailing 3 bytes of the input, which are
 * *not* stripped (see harness_0):
 *   byte -1   output major index (harness_majors)
 *   byte -2   output codec index (harness_codecs); 0xff keeps the input codec
 *   byte -3   bits 0-1 sample type (short/int/float/double),
 *             bits 2-3 output endianness, bit 4 disable float normalisation
 *
 * This reaches the encoder bugs with *decoded* data instead of raw fuzz
 * bytes, e.g. NaN / infinite floats or INT_MIN samples read from a float or
 * PCM32 file, and strings / cue names read from LIST, AIFF or CAF chunks:
 *
 *   SND010 012 013  strings / cue names copied into WAV or AIFF headers
 *   SND014 022      float/double input containing NaN or Inf -> A-law/u-law
 *   SND015 023      32-bit PCM input containing INT_MIN -> A-law/u-law
 *   plus every decoder bug in harness_0 that sf_open_virtual can reach.
 */

#include "harness.h"

static void copy_metadata(SNDFILE *in, SNDFILE *out, int channels) {
  SF_INSTRUMENT inst;
  SF_BROADCAST_INFO bext;
  SF_CART_INFO cart;
  uint32_t ncues = 0;
  int k;

  for (k = SF_STR_FIRST; k <= SF_STR_LAST; k++) {
    const char *s = sf_get_string(in, k);
    if (s != NULL)
      sf_set_string(out, k, s);
  }

  if (sf_command(in, SFC_GET_INSTRUMENT, &inst, sizeof inst) == SF_TRUE)
    sf_command(out, SFC_SET_INSTRUMENT, &inst, sizeof inst);

  if (sf_command(in, SFC_GET_CUE_COUNT, &ncues, sizeof ncues) && ncues > 0) {
    SF_CUES *cues;
    size_t sz;
    if (ncues > 100)
      ncues = 100;
    sz = sizeof(uint32_t) + ncues * sizeof(SF_CUE_POINT);
    if ((cues = (SF_CUES *)calloc(1, sz)) != NULL) {
      if (sf_command(in, SFC_GET_CUE, cues, (int)sz) == SF_TRUE)
        sf_command(out, SFC_SET_CUE, cues, (int)sz);
      free(cues);
    }
  }

  if (sf_command(in, SFC_GET_BROADCAST_INFO, &bext, sizeof bext) == SF_TRUE)
    sf_command(out, SFC_SET_BROADCAST_INFO, &bext, sizeof bext);

  if (sf_command(in, SFC_GET_CART_INFO, &cart, sizeof cart) == SF_TRUE)
    sf_command(out, SFC_SET_CART_INFO, &cart, sizeof cart);

  if (channels <= 1024) {
    int *map = (int *)calloc((size_t)channels, sizeof(int));
    if (map != NULL) {
      if (sf_command(in, SFC_GET_CHANNEL_MAP_INFO, map,
                     channels * (int)sizeof(int)) == SF_TRUE)
        sf_command(out, SFC_SET_CHANNEL_MAP_INFO, map,
                   channels * (int)sizeof(int));
      free(map);
    }
  }
}

static int fuzz_one(const uint8_t *data, size_t size) {
  vio_in vin = {data, (sf_count_t)size, 0};
  vio_out vout = {NULL, 0, 0, 0};
  SF_INFO iinfo, oinfo;
  SNDFILE *in, *out;
  uint8_t omajor, ocodec, opts;
  int type;

  if (size < 4)
    return 0;
  omajor = data[size - 1];
  ocodec = data[size - 2];
  opts = data[size - 3];
  type = opts & 3;

  memset(&iinfo, 0, sizeof iinfo);
  if ((in = sf_open_virtual(&vio_in_ops, SFM_READ, &iinfo, &vin)) == NULL)
    return 0;

  oinfo = iinfo;
  oinfo.format = harness_majors[omajor % HARNESS_N_MAJORS] |
                 (ocodec == 0xff ? (iinfo.format & SF_FORMAT_SUBMASK)
                                 : harness_codecs[ocodec % HARNESS_N_CODECS]) |
                 harness_endians[(opts >> 2) & 3];
  if (oinfo.samplerate < 1)
    oinfo.samplerate = 8000;

  if (!sf_format_check(&oinfo) ||
      (out = sf_open_virtual(&vio_out_ops, SFM_WRITE, &oinfo, &vout)) == NULL) {
    sf_close(in);
    free(vout.buf);
    return 0;
  }

  if (opts & 0x10) {
    sf_command(in, SFC_SET_NORM_FLOAT, NULL, SF_FALSE);
    sf_command(in, SFC_SET_NORM_DOUBLE, NULL, SF_FALSE);
    sf_command(out, SFC_SET_NORM_FLOAT, NULL, SF_FALSE);
    sf_command(out, SFC_SET_NORM_DOUBLE, NULL, SF_FALSE);
  }

  copy_metadata(in, out, iinfo.channels);
  harness_pump(in, out, iinfo.channels, type);

  sf_close(out);
  sf_close(in);
  free(vout.buf);
  return 0;
}
