/* Decoder: open the input as an audio file, query every piece of metadata
 * and decode the samples.
 *
 * Configuration comes from the trailing 4 bytes of the input, which are *not*
 * stripped (trailing bytes after audio data are harmless for nearly every
 * container, so seed files decode unchanged and mutating the tail changes the
 * configuration). With c = last byte:
 *
 *   c & 3     open mode: 0, 1  sf_open_virtual, format auto-detected
 *                        2     sf_open_virtual as SF_FORMAT_RAW; codec,
 *                              endianness and channel count from bytes -2..-4
 *                        3     sf_open on a real path; the input is also
 *                              dropped next to it as an AppleDouble "._" file
 *                              so the SD2 resource-fork parser is reachable
 *   c >> 2 & 3  sample type (short / int / float / double)
 *   c & 0x10    turn off float normalisation / enable float->int scaling
 *   c & 0x20    seek back to the middle and decode a second time
 *   c & 0x40    SFC_CALC_SIGNAL_MAX / SFC_CALC_MAX_ALL_CHANNELS
 *
 *   SND001  PAF header with channels < 1 or > SF_MAX_CHANNELS
 *   SND002  SD2 resource fork, map offset check (reach-only, see below)
 *   SND005  AIFF CHAN chunk whose layout tag has fewer channels than COMM
 *   SND006  FLAC frame whose channel count differs from STREAMINFO
 *   SND007  FLAC with a second STREAMINFO block changing the sample rate
 *   SND016  MAT5 double array with rows (channels) > SF_MAX_CHANNELS; the
 *           RAW mode cannot reach it, sf_format_check rejects such SF_INFO
 *   SND017  WAVE_FORMAT_EXTENSIBLE channel mask with more bits than channels
 *   SND020  WAVE_FORMAT_EXTENSIBLE channel mask with no known speaker bits
 *   SND024  FLAC with a second STREAMINFO block changing the channel count
 *
 * SND002's canary (map_offset + 28 > rsrc_len) is dominated by the preceding
 * `map_offset + 28 >= rsrc_len` rejection in sd2_parse_rsrc_fork, and the
 * earlier consistency checks force 0 <= map_offset <= rsrc_len, so it can be
 * reached but not triggered at this libsndfile revision.
 */

#include "harness.h"

#include <unistd.h>

static void query_metadata(SNDFILE *sf, const SF_INFO *info) {
  static char log[16384];
  SF_INFO cur;
  SF_INSTRUMENT inst;
  SF_LOOP_INFO loop;
  SF_BROADCAST_INFO bext;
  SF_CART_INFO cart;
  SF_EMBED_FILE_INFO embed;
  uint32_t ncues;
  int k, *chanmap;

  sf_command(sf, SFC_GET_LOG_INFO, log, sizeof log);
  sf_command(sf, SFC_GET_CURRENT_SF_INFO, &cur, sizeof cur);
  sf_command(sf, SFC_GET_INSTRUMENT, &inst, sizeof inst);
  sf_command(sf, SFC_GET_LOOP_INFO, &loop, sizeof loop);
  sf_command(sf, SFC_GET_BROADCAST_INFO, &bext, sizeof bext);
  sf_command(sf, SFC_GET_CART_INFO, &cart, sizeof cart);
  sf_command(sf, SFC_GET_EMBED_FILE_INFO, &embed, sizeof embed);
  sf_command(sf, SFC_RAW_DATA_NEEDS_ENDSWAP, NULL, 0);

  if (sf_command(sf, SFC_GET_CUE_COUNT, &ncues, sizeof ncues) && ncues > 0) {
    SF_CUES *cues;
    size_t sz;
    if (ncues > 1000)
      ncues = 1000;
    sz = sizeof(uint32_t) + ncues * sizeof(SF_CUE_POINT);
    if ((cues = (SF_CUES *)malloc(sz)) != NULL) {
      sf_command(sf, SFC_GET_CUE, cues, (int)sz);
      free(cues);
    }
  }

  if (info->channels > 0 && info->channels <= 1024 &&
      (chanmap = (int *)calloc((size_t)info->channels, sizeof(int))) != NULL) {
    sf_command(sf, SFC_GET_CHANNEL_MAP_INFO, chanmap,
               info->channels * (int)sizeof(int));
    free(chanmap);
  }

  for (k = SF_STR_FIRST; k <= SF_STR_LAST; k++)
    sf_get_string(sf, k);
}

static void decode(SNDFILE *sf, const SF_INFO *info, uint8_t c) {
  int type = (c >> 2) & 3;

  query_metadata(sf, info);

  if (c & 0x10) {
    sf_command(sf, SFC_SET_NORM_FLOAT, NULL, SF_FALSE);
    sf_command(sf, SFC_SET_NORM_DOUBLE, NULL, SF_FALSE);
    sf_command(sf, SFC_SET_SCALE_FLOAT_INT_READ, NULL, SF_TRUE);
  }

  if ((c & 0x40) && info->channels > 0 && info->channels <= 1024) {
    double one, *all = (double *)calloc((size_t)info->channels, sizeof(double));
    sf_command(sf, SFC_CALC_SIGNAL_MAX, &one, sizeof one);
    if (all != NULL) {
      sf_command(sf, SFC_CALC_MAX_ALL_CHANNELS, all,
                 info->channels * (int)sizeof(double));
      free(all);
    }
    sf_seek(sf, 0, SEEK_SET);
  }

  harness_pump(sf, NULL, info->channels, type);

  if (c & 0x20) {
    sf_seek(sf, info->frames / 2, SEEK_SET);
    harness_pump(sf, NULL, info->channels, (type + 1) & 3);
  }
}

/* Open through the filesystem. The input is written to <tmp>/f and to its
 * AppleDouble resource fork <tmp>/._f, which libsndfile looks for when no
 * other container matches (try_resource_fork -> SD2). */
static void decode_path(const uint8_t *data, size_t size, uint8_t c) {
  char dir[] = "/tmp/sndfile-hw-XXXXXX";
  char path[64], rsrc[64];
  FILE *f;
  SF_INFO info;
  SNDFILE *sf;

  if (mkdtemp(dir) == NULL)
    return;
  snprintf(path, sizeof path, "%s/f", dir);
  snprintf(rsrc, sizeof rsrc, "%s/._f", dir);

  if ((f = fopen(path, "wb")) != NULL) {
    fwrite(data, 1, size, f);
    fclose(f);
  }
  if ((f = fopen(rsrc, "wb")) != NULL) {
    fwrite(data, 1, size, f);
    fclose(f);
  }

  memset(&info, 0, sizeof info);
  if ((sf = sf_open(path, SFM_READ, &info)) != NULL) {
    decode(sf, &info, c);
    sf_close(sf);
  }

  unlink(rsrc);
  unlink(path);
  rmdir(dir);
}

static int fuzz_one(const uint8_t *data, size_t size) {
  vio_in in = {data, (sf_count_t)size, 0};
  SF_INFO info;
  SNDFILE *sf;
  uint8_t c = data[size - 1];

  memset(&info, 0, sizeof info);

  switch (c & 3) {
  case 3:
    decode_path(data, size, c);
    return 0;
  case 2:
    if (size < 4)
      return 0;
    /* bytes -4,-3: channels - 1 (11 bits, up to 2048), bits 11-12: endian;
     * byte -2: codec index. */
    {
      unsigned w = data[size - 4] | (unsigned)data[size - 3] << 8;
      info.channels = (int)(w & 0x7ff) + 1;
      info.samplerate = 44100;
      info.format = SF_FORMAT_RAW |
                    harness_codecs[data[size - 2] % HARNESS_N_CODECS] |
                    harness_endians[(w >> 11) & 3];
    }
    break;
  default:
    break;
  }

  if ((sf = sf_open_virtual(&vio_in_ops, SFM_READ, &info, &in)) == NULL)
    return 0;
  decode(sf, &info, c);
  sf_close(sf);
  return 0;
}
