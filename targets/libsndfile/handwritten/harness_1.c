/* Encoder: the input describes a file to write — container, codec, channel
 * count, sample rate, metadata (strings, instrument, cues, broadcast / cart
 * chunks, channel map) and sample data — which is written to an in-memory
 * SF_VIRTUAL_IO and optionally reopened for read or read/write.
 *
 * Layout (little endian; missing bytes read as 0):
 *   u8  major index        (harness_majors)
 *   u8  codec index        (harness_codecs)
 *   u8  opts   bits 0-1 endianness, 2-3 sample type (short/int/float/double),
 *              4 sf_write_raw instead of typed writes,
 *              5 SFC_SET_UPDATE_HEADER_AUTO, 6 SFC_SET_ADD_PEAK_CHUNK,
 *              7 after close, reopen: SFM_RDWR + append (else SFM_READ + decode)
 *   u16 channels - 1       (& 0x3ff)
 *   u24 samplerate - 1
 *   u8  meta   bit 0 strings, 1 instrument, 2 cues, 3 broadcast, 4 cart,
 *              5 channel map, 6 SFC_UPDATE_HEADER_NOW between chunks,
 *              7 SFC_SET_CLIPPING
 *   [strings]    u8 n (& 15), then n * { u8 type, u16 len (& 0x7ff), bytes }
 *   [instrument] sizeof (SF_INSTRUMENT) raw bytes (loop_count unrestricted)
 *   [cues]       u8 n (% 101), then n * { u32 indx, u32 offset, u8 len, name }
 *   [broadcast]  sizeof (SF_BROADCAST_INFO) raw bytes
 *   [cart]       sizeof (SF_CART_INFO) raw bytes
 *   [chanmap]    channels bytes, one SF_CHANNEL_MAP_* value each
 *   rest         sample data, written in chunks of 1 + (u8 * 8) frames
 *
 *   SND004  psf_fwrite called with a zero byte or item count
 *   SND010  WAV LIST/INFO string ('s' in psf_binheader_writef), even length
 *   SND012  AIFF string chunk ('S') larger than the remaining header buffer
 *   SND013  AIFF MARK cue name ('p') larger than the remaining header buffer
 *   SND014  A-law, sf_write_double with a NaN / infinity
 *   SND015  A-law, sf_write_int with INT_MIN
 *   SND022  u-law, sf_write_double with a NaN / infinity
 *   SND023  u-law, sf_write_int with INT_MIN
 *   SND025  WAV smpl chunk from SFC_SET_INSTRUMENT with loop_count > 16
 */

#include "harness.h"

#define MAX_STRING 2047

static void set_metadata(SNDFILE *sf, provider *pv, int channels,
                         uint8_t meta) {
  if (meta & 1) {
    unsigned n = take(pv, 1) & 15, i;
    static char str[MAX_STRING + 1];
    for (i = 0; i < n; i++) {
      int type = SF_STR_FIRST + (int)(take(pv, 1) % SF_STR_LAST);
      size_t len = take(pv, 2) & MAX_STRING;
      take_bytes(pv, str, len);
      str[len] = 0;
      sf_set_string(sf, type, str);
    }
  }

  if (meta & 2) {
    SF_INSTRUMENT inst;
    take_bytes(pv, &inst, sizeof inst);
    sf_command(sf, SFC_SET_INSTRUMENT, &inst, sizeof inst);
  }

  if (meta & 4) {
    static SF_CUES cues;
    unsigned i;
    memset(&cues, 0, sizeof cues);
    cues.cue_count = take(pv, 1) % 101;
    for (i = 0; i < cues.cue_count; i++) {
      size_t len;
      cues.cue_points[i].indx = (int32_t)take(pv, 4);
      cues.cue_points[i].sample_offset = take(pv, 4);
      cues.cue_points[i].position = cues.cue_points[i].sample_offset;
      len = take(pv, 1);
      take_bytes(pv, cues.cue_points[i].name, len);
      cues.cue_points[i].name[len < 255 ? len : 255] = 0;
    }
    sf_command(sf, SFC_SET_CUE, &cues, sizeof cues);
  }

  if (meta & 8) {
    SF_BROADCAST_INFO bext;
    take_bytes(pv, &bext, sizeof bext);
    bext.coding_history_size %= sizeof bext.coding_history + 1;
    sf_command(sf, SFC_SET_BROADCAST_INFO, &bext, sizeof bext);
  }

  if (meta & 16) {
    SF_CART_INFO cart;
    take_bytes(pv, &cart, sizeof cart);
    cart.tag_text_size %= sizeof cart.tag_text + 1;
    sf_command(sf, SFC_SET_CART_INFO, &cart, sizeof cart);
  }

  if (meta & 32) {
    int *map = (int *)calloc((size_t)channels, sizeof(int));
    int i;
    if (map != NULL) {
      for (i = 0; i < channels; i++)
        map[i] = (int)(take(pv, 1) % (SF_CHANNEL_MAP_MAX + 1));
      sf_command(sf, SFC_SET_CHANNEL_MAP_INFO, map,
                 channels * (int)sizeof(int));
      free(map);
    }
  }

  if (meta & 128)
    sf_command(sf, SFC_SET_CLIPPING, NULL, SF_TRUE);
}

/* Write the rest of the input as samples. Each chunk is prefixed by a byte
 * selecting its length so the fuzzer controls the write call boundaries. */
static void write_samples(SNDFILE *sf, provider *pv, int channels, int type,
                          int raw, int update_now) {
  size_t width = (type == XFER_SHORT)    ? sizeof(short)
                 : (type == XFER_INT)    ? sizeof(int)
                 : (type == XFER_FLOAT)  ? sizeof(float)
                                         : sizeof(double);
  sf_count_t total = 0;
  uint8_t *buf;
  size_t max_frames = 1 + 255 * 8;

  buf = (uint8_t *)malloc(max_frames * (size_t)channels * width);
  if (buf == NULL)
    return;

  while (pv->left > 0 && total < HARNESS_MAX_FRAMES) {
    sf_count_t frames = 1 + (sf_count_t)take(pv, 1) * 8;
    size_t avail = pv->left / ((size_t)channels * width);
    if (avail == 0)
      break;
    if ((size_t)frames > avail)
      frames = (sf_count_t)avail;
    take_bytes(pv, buf, (size_t)frames * (size_t)channels * width);

    if (raw)
      sf_write_raw(sf, buf, frames * channels * (sf_count_t)width);
    else
      switch (type) {
      case XFER_SHORT: sf_writef_short(sf, (short *)buf, frames); break;
      case XFER_INT: sf_writef_int(sf, (int *)buf, frames); break;
      case XFER_FLOAT: sf_writef_float(sf, (float *)buf, frames); break;
      default: sf_writef_double(sf, (double *)buf, frames); break;
      }

    if (update_now)
      sf_command(sf, SFC_UPDATE_HEADER_NOW, NULL, 0);
    total += frames;
  }
  free(buf);
}

static int fuzz_one(const uint8_t *data, size_t size) {
  provider pv = {data, size};
  vio_out out = {NULL, 0, 0, 0};
  SF_INFO info;
  SNDFILE *sf;
  unsigned major, codec;
  uint8_t opts, meta;
  int type;

  if (size < 9)
    return 0;

  major = take(&pv, 1);
  codec = take(&pv, 1);
  opts = (uint8_t)take(&pv, 1);
  type = (opts >> 2) & 3;

  memset(&info, 0, sizeof info);
  info.format = harness_format(major, codec, opts & 3);
  info.channels = (int)(take(&pv, 2) & 0x3ff) + 1;
  info.samplerate = (int)take(&pv, 3) + 1;
  meta = (uint8_t)take(&pv, 1);

  if (!sf_format_check(&info))
    return 0;

  if ((sf = sf_open_virtual(&vio_out_ops, SFM_WRITE, &info, &out)) == NULL)
    goto done;

  if (opts & 0x20)
    sf_command(sf, SFC_SET_UPDATE_HEADER_AUTO, NULL, SF_TRUE);
  if (opts & 0x40)
    sf_command(sf, SFC_SET_ADD_PEAK_CHUNK, NULL, SF_TRUE);

  set_metadata(sf, &pv, info.channels, meta);
  write_samples(sf, &pv, info.channels, type, opts & 0x10, meta & 64);
  sf_close(sf);

  /* Round trip through the bytes just produced. */
  out.pos = 0;
  if (opts & 0x80) {
    SF_INFO again = info;
    if ((sf = sf_open_virtual(&vio_out_ops, SFM_RDWR, &again, &out)) != NULL) {
      static const uint8_t tail[64];
      provider more = {tail, sizeof tail};
      sf_seek(sf, 0, SEEK_END);
      write_samples(sf, &more, again.channels, type, 0, 0);
      sf_close(sf);
    }
  } else {
    SF_INFO again;
    memset(&again, 0, sizeof again);
    if ((info.format & SF_FORMAT_TYPEMASK) == SF_FORMAT_RAW)
      again = info;
    if ((sf = sf_open_virtual(&vio_out_ops, SFM_READ, &again, &out)) != NULL) {
      harness_pump(sf, NULL, again.channels, type);
      sf_close(sf);
    }
  }

done:
  free(out.buf);
  return 0;
}
