/* Shared plumbing for the hand-written libsndfile harnesses.
 *
 * Each harness defines `static int fuzz_one(const uint8_t *, size_t)`; this
 * header supplies a file-reading main() (AFL `@@` style, matching the traffic
 * and ogharn harnesses) plus:
 *
 *  - in-memory SF_VIRTUAL_IO for reading (const input) and writing (growable,
 *    capped buffer), so encoders run without touching the filesystem;
 *  - a byte provider for structured inputs;
 *  - format / codec tables shared by the encoder and transcoder harnesses;
 *  - bounded sample-transfer helpers (short / int / float / double).
 */

#ifndef LIBSNDFILE_HANDWRITTEN_HARNESS_H
#define LIBSNDFILE_HANDWRITTEN_HARNESS_H

#include <sndfile.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Upper bound on frames moved per input, keeps every exec short. */
#ifndef HARNESS_MAX_FRAMES
#define HARNESS_MAX_FRAMES (1 << 16)
#endif

/* Samples per transfer call (buffer = HARNESS_CHUNK * channels). */
#define HARNESS_CHUNK 1024

/* Largest output the write VIO will hold. Writes past it are short. */
#define HARNESS_MAX_OUT ((sf_count_t)64 << 20)

/* ---- byte provider ------------------------------------------------------- */

typedef struct {
  const uint8_t *p;
  size_t left;
} provider;

static inline uint32_t take(provider *pv, size_t nbytes) {
  uint32_t v = 0;
  size_t i;
  for (i = 0; i < nbytes && pv->left > 0; i++) {
    v |= (uint32_t)*pv->p++ << (8 * i);
    pv->left--;
  }
  return v;
}

static inline void take_bytes(provider *pv, void *out, size_t n) {
  size_t k = n < pv->left ? n : pv->left;
  memcpy(out, pv->p, k);
  memset((uint8_t *)out + k, 0, n - k);
  pv->p += k;
  pv->left -= k;
}

/* ---- read VIO ------------------------------------------------------------- */

typedef struct {
  const uint8_t *data;
  sf_count_t size, pos;
} vio_in;

static sf_count_t in_len(void *u) { return ((vio_in *)u)->size; }

static sf_count_t in_seek(sf_count_t off, int whence, void *u) {
  vio_in *v = (vio_in *)u;
  sf_count_t np;
  switch (whence) {
  case SEEK_SET: np = off; break;
  case SEEK_CUR: np = v->pos + off; break;
  case SEEK_END: np = v->size + off; break;
  default: return -1;
  }
  if (np < 0)
    return -1;
  v->pos = np;
  return np;
}

static sf_count_t in_read(void *ptr, sf_count_t count, void *u) {
  vio_in *v = (vio_in *)u;
  sf_count_t n;
  if (count <= 0 || v->pos >= v->size)
    return 0;
  n = v->size - v->pos;
  if (n > count)
    n = count;
  memcpy(ptr, v->data + v->pos, (size_t)n);
  v->pos += n;
  return n;
}

static sf_count_t in_write(const void *ptr, sf_count_t count, void *u) {
  (void)ptr; (void)count; (void)u;
  return 0;
}

static sf_count_t in_tell(void *u) { return ((vio_in *)u)->pos; }

static SF_VIRTUAL_IO vio_in_ops = {in_len, in_seek, in_read, in_write, in_tell};

/* ---- write VIO ------------------------------------------------------------ */

typedef struct {
  uint8_t *buf;
  sf_count_t len, cap, pos;
} vio_out;

static sf_count_t out_len(void *u) { return ((vio_out *)u)->len; }

static sf_count_t out_seek(sf_count_t off, int whence, void *u) {
  vio_out *v = (vio_out *)u;
  sf_count_t np;
  switch (whence) {
  case SEEK_SET: np = off; break;
  case SEEK_CUR: np = v->pos + off; break;
  case SEEK_END: np = v->len + off; break;
  default: return -1;
  }
  if (np < 0 || np > HARNESS_MAX_OUT)
    return -1;
  v->pos = np;
  return np;
}

static sf_count_t out_read(void *ptr, sf_count_t count, void *u) {
  vio_out *v = (vio_out *)u;
  sf_count_t n;
  if (count <= 0 || v->pos >= v->len)
    return 0;
  n = v->len - v->pos;
  if (n > count)
    n = count;
  memcpy(ptr, v->buf + v->pos, (size_t)n);
  v->pos += n;
  return n;
}

static sf_count_t out_write(const void *ptr, sf_count_t count, void *u) {
  vio_out *v = (vio_out *)u;
  sf_count_t end;
  if (count <= 0)
    return 0;
  if (count > HARNESS_MAX_OUT - v->pos)
    count = HARNESS_MAX_OUT - v->pos;
  end = v->pos + count;
  if (end > v->cap) {
    sf_count_t nc = v->cap ? v->cap : 4096;
    uint8_t *nb;
    while (nc < end)
      nc *= 2;
    if (nc > HARNESS_MAX_OUT)
      nc = HARNESS_MAX_OUT;
    if ((nb = (uint8_t *)realloc(v->buf, (size_t)nc)) == NULL)
      return 0;
    v->buf = nb;
    v->cap = nc;
  }
  if (v->pos > v->len)
    memset(v->buf + v->len, 0, (size_t)(v->pos - v->len));
  memcpy(v->buf + v->pos, ptr, (size_t)count);
  v->pos = end;
  if (end > v->len)
    v->len = end;
  return count;
}

static sf_count_t out_tell(void *u) { return ((vio_out *)u)->pos; }

static SF_VIRTUAL_IO vio_out_ops = {out_len, out_seek, out_read, out_write,
                                    out_tell};

/* ---- format tables -------------------------------------------------------- */

static const int harness_majors[] = {
    SF_FORMAT_WAV,  SF_FORMAT_AIFF, SF_FORMAT_AU,   SF_FORMAT_RAW,
    SF_FORMAT_PAF,  SF_FORMAT_SVX,  SF_FORMAT_NIST, SF_FORMAT_VOC,
    SF_FORMAT_IRCAM, SF_FORMAT_W64, SF_FORMAT_MAT4, SF_FORMAT_MAT5,
    SF_FORMAT_PVF,  SF_FORMAT_XI,   SF_FORMAT_HTK,  SF_FORMAT_SDS,
    SF_FORMAT_AVR,  SF_FORMAT_WAVEX, SF_FORMAT_SD2, SF_FORMAT_FLAC,
    SF_FORMAT_CAF,  SF_FORMAT_WVE,  SF_FORMAT_OGG,  SF_FORMAT_MPC2K,
    SF_FORMAT_RF64, SF_FORMAT_MPEG,
};
#define HARNESS_N_MAJORS (sizeof harness_majors / sizeof harness_majors[0])

static const int harness_codecs[] = {
    SF_FORMAT_PCM_S8,    SF_FORMAT_PCM_16,    SF_FORMAT_PCM_24,
    SF_FORMAT_PCM_32,    SF_FORMAT_PCM_U8,    SF_FORMAT_FLOAT,
    SF_FORMAT_DOUBLE,    SF_FORMAT_ULAW,      SF_FORMAT_ALAW,
    SF_FORMAT_IMA_ADPCM, SF_FORMAT_MS_ADPCM,  SF_FORMAT_GSM610,
    SF_FORMAT_VOX_ADPCM, SF_FORMAT_NMS_ADPCM_16, SF_FORMAT_NMS_ADPCM_24,
    SF_FORMAT_NMS_ADPCM_32, SF_FORMAT_G721_32, SF_FORMAT_G723_24,
    SF_FORMAT_G723_40,   SF_FORMAT_DWVW_12,   SF_FORMAT_DWVW_16,
    SF_FORMAT_DWVW_24,   SF_FORMAT_DWVW_N,    SF_FORMAT_DPCM_8,
    SF_FORMAT_DPCM_16,   SF_FORMAT_VORBIS,    SF_FORMAT_OPUS,
    SF_FORMAT_ALAC_16,   SF_FORMAT_ALAC_20,   SF_FORMAT_ALAC_24,
    SF_FORMAT_ALAC_32,   SF_FORMAT_MPEG_LAYER_III,
};
#define HARNESS_N_CODECS (sizeof harness_codecs / sizeof harness_codecs[0])

static const int harness_endians[] = {SF_ENDIAN_FILE, SF_ENDIAN_LITTLE,
                                      SF_ENDIAN_BIG, SF_ENDIAN_CPU};

static inline int harness_format(unsigned major, unsigned codec,
                                 unsigned endian) {
  return harness_majors[major % HARNESS_N_MAJORS] |
         harness_codecs[codec % HARNESS_N_CODECS] | harness_endians[endian & 3];
}

/* ---- sample transfer ------------------------------------------------------ */

enum { XFER_SHORT, XFER_INT, XFER_FLOAT, XFER_DOUBLE };

/* Read up to HARNESS_MAX_FRAMES frames from `in` with sf_readf_<type>.
 * If `out` is non-NULL every chunk read is written to it with the same type. */
static inline void harness_pump(SNDFILE *in, SNDFILE *out, int channels,
                                int type) {
  void *buf;
  sf_count_t total = 0, n;
  size_t width = (type == XFER_SHORT)    ? sizeof(short)
                 : (type == XFER_INT)    ? sizeof(int)
                 : (type == XFER_FLOAT)  ? sizeof(float)
                                         : sizeof(double);

  if (channels < 1 || channels > 4096)
    return;
  buf = calloc((size_t)HARNESS_CHUNK * (size_t)channels, width);
  if (buf == NULL)
    return;

  while (total < HARNESS_MAX_FRAMES) {
    switch (type) {
    case XFER_SHORT: n = sf_readf_short(in, (short *)buf, HARNESS_CHUNK); break;
    case XFER_INT: n = sf_readf_int(in, (int *)buf, HARNESS_CHUNK); break;
    case XFER_FLOAT: n = sf_readf_float(in, (float *)buf, HARNESS_CHUNK); break;
    default: n = sf_readf_double(in, (double *)buf, HARNESS_CHUNK); break;
    }
    if (n <= 0)
      break;
    if (out != NULL) {
      switch (type) {
      case XFER_SHORT: sf_writef_short(out, (short *)buf, n); break;
      case XFER_INT: sf_writef_int(out, (int *)buf, n); break;
      case XFER_FLOAT: sf_writef_float(out, (float *)buf, n); break;
      default: sf_writef_double(out, (double *)buf, n); break;
      }
    }
    total += n;
  }
  free(buf);
}

/* ---- main ----------------------------------------------------------------- */

/* Path of the input file, for harnesses that open through the filesystem. */
static const char *harness_path;

static int fuzz_one(const uint8_t *data, size_t size);

int main(int argc, char *argv[]) {
  FILE *f;
  long size;
  uint8_t *buf;
  int ret;

  if (argc < 2)
    return 0;
  harness_path = argv[1];

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

#endif /* LIBSNDFILE_HANDWRITTEN_HARNESS_H */
