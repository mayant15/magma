/* Crypto-library consumer: ASN.1, PKCS#7, BIGNUM and streaming encoders.
 *
 * The first byte selects a mode (byte % 5); the rest is mode specific.
 *
 *  0  ASN.1 round trip. The rest is decoded as SEQUENCE OF ANY, SET OF ANY
 *     and as a stream of ANY values; everything decoded is re-encoded and
 *     neighbouring values are compared with ASN1_TYPE_cmp.
 *       SSL001  ANY with universal tag 258 (NEG_INTEGER) and content 0x00
 *       SSL014  two BOOLEAN values compared
 *
 *  1  PKCS#7 consumer (`openssl smime -decrypt / -verify` flow) with the
 *     embedded key/certificate as recipient. The rest is a DER ContentInfo.
 *       SSL011  signedData without content, no detached content supplied
 *       SSL015  ContentInfo without [0] content
 *
 *  2  GF(2^m) arithmetic: <u16 len><p> <u16 len><a> <u16 len><b>
 *     (big-endian magnitudes). Inverse, division, sqrt, quadratic solve.
 *       SSL016  inverse modulo a reducible polynomial
 *
 *  3  BIGNUM text parsing: <u8 kind> <u32 len> <pattern...>. The text is
 *     `len` bytes made by repeating `pattern` (or just `pattern` if len is
 *     smaller), modelling a number read from a large text file / config.
 *     kind % 3: BN_hex2bn, BN_dec2bn, BN_asc2bn.
 *       SSL010  >= INT_MAX/4 digits (512 MiB; capped at HARNESS_MAX_TEXT)
 *
 *  4  Streaming hash / encoder: a sequence of updates <u8 op> <u32 len>
 *     [<len bytes>]. op bit 0: target (0 = base64 EVP_Encode, 1 = MDC2);
 *     op bit 1: also run base64 decoding over the same bytes; op bit 7:
 *     "large" update whose bytes are not in the input: `len` zero bytes
 *     from a lazily mapped region (a big file mmap'ed by an application).
 *       SSL006  one EVP_EncodeUpdate of > INT_MAX - 48 bytes after a
 *               partial line
 *       SSL007  reach only: needs an MDC2_Update length near SIZE_MAX
 */

/* MDC2_* and the GF(2^m) helpers are deprecated low-level APIs. */
#define OPENSSL_SUPPRESS_DEPRECATED

#include "harness.h"

#include <openssl/asn1.h>
#include <openssl/bn.h>
#include <openssl/mdc2.h>
#include <openssl/pkcs7.h>

#include <sys/mman.h>

/* Largest synthesized text (mode 3) / zero region (mode 4). */
#ifndef HARNESS_MAX_TEXT
#define HARNESS_MAX_TEXT ((size_t)1 << 29) /* INT_MAX / 4 + 1 digits */
#endif
#ifndef HARNESS_MAX_ZERO
#define HARNESS_MAX_ZERO ((size_t)INT_MAX)
#endif

/* ---- 0: ASN.1 ---------------------------------------------------------------- */

static void reencode_types(STACK_OF(ASN1_TYPE) *sk) {
  int i;
  unsigned char *der;
  for (i = 0; i < sk_ASN1_TYPE_num(sk); i++) {
    der = NULL;
    if (i2d_ASN1_TYPE(sk_ASN1_TYPE_value(sk, i), &der) > 0)
      OPENSSL_free(der);
    if (i > 0)
      (void)ASN1_TYPE_cmp(sk_ASN1_TYPE_value(sk, i - 1),
                          sk_ASN1_TYPE_value(sk, i));
  }
}

static void mode_asn1(const uint8_t *data, size_t size) {
  const unsigned char *p;
  unsigned char *der;
  ASN1_SEQUENCE_ANY *sq;
  ASN1_TYPE *t;
  STACK_OF(ASN1_TYPE) *stream;

  p = data;
  if ((sq = d2i_ASN1_SEQUENCE_ANY(NULL, &p, (long)size)) != NULL) {
    reencode_types(sq);
    der = NULL;
    if (i2d_ASN1_SEQUENCE_ANY(sq, &der) > 0)
      OPENSSL_free(der);
    sk_ASN1_TYPE_pop_free(sq, ASN1_TYPE_free);
  }

  p = data;
  if ((sq = d2i_ASN1_SET_ANY(NULL, &p, (long)size)) != NULL) {
    reencode_types(sq);
    der = NULL;
    if (i2d_ASN1_SET_ANY(sq, &der) > 0)
      OPENSSL_free(der);
    sk_ASN1_TYPE_pop_free(sq, ASN1_TYPE_free);
  }

  stream = sk_ASN1_TYPE_new_null();
  p = data;
  while (stream != NULL && p < data + size &&
         (t = d2i_ASN1_TYPE(NULL, &p, (long)(data + size - p))) != NULL)
    if (!sk_ASN1_TYPE_push(stream, t))
      ASN1_TYPE_free(t);
  reencode_types(stream);
  sk_ASN1_TYPE_pop_free(stream, ASN1_TYPE_free);
}

/* ---- 1: PKCS#7 --------------------------------------------------------------- */

static void drain(BIO *b) {
  char buf[512];
  while (BIO_read(b, buf, sizeof buf) > 0)
    ;
}

static void mode_pkcs7(const uint8_t *data, size_t size) {
  const unsigned char *p = data;
  PKCS7 *p7;
  EVP_PKEY *key;
  X509 *cert;
  X509_STORE *store;
  BIO *bio, *out;

  if ((p7 = d2i_PKCS7(NULL, &p, (long)size)) == NULL)
    return;

  key = harness_load_key();
  cert = harness_load_cert();
  store = X509_STORE_new();
  if (cert != NULL && store != NULL)
    X509_STORE_add_cert(store, cert);

  /* Low-level decode as in apps that stream the content themselves: no
   * detached content is supplied, the inner content is expected. */
  if ((bio = PKCS7_dataDecode(p7, key, NULL, cert)) != NULL) {
    drain(bio);
    BIO_free_all(bio);
  }

  out = BIO_new(BIO_s_null());
  if (PKCS7_type_is_enveloped(p7))
    (void)PKCS7_decrypt(p7, key, cert, out, 0);
  if (PKCS7_type_is_signed(p7))
    (void)PKCS7_verify(p7, NULL, store, NULL, out, PKCS7_NOVERIFY);
  BIO_free(out);

  X509_STORE_free(store);
  X509_free(cert);
  EVP_PKEY_free(key);
  PKCS7_free(p7);
}

/* ---- 2: GF(2^m) -------------------------------------------------------------- */

static BIGNUM *take_bn(harness_cur *c) {
  harness_cur s = harness_slice16(c);
  return BN_bin2bn(s.data, (int)s.left, NULL);
}

static void mode_gf2m(const uint8_t *data, size_t size) {
  harness_cur c = {data, size};
  BIGNUM *p = take_bn(&c), *a = take_bn(&c), *b = take_bn(&c);
  BIGNUM *r = BN_new();
  BN_CTX *ctx = BN_CTX_new();

  if (p == NULL || a == NULL || b == NULL || r == NULL || ctx == NULL ||
      BN_is_zero(p) || BN_num_bits(p) > 4096)
    goto end;

  (void)BN_GF2m_mod_inv(r, a, p, ctx);
  (void)BN_GF2m_mod_div(r, b, a, p, ctx);
  (void)BN_GF2m_mod_mul(r, a, b, p, ctx);
  (void)BN_GF2m_mod_sqrt(r, a, p, ctx);
  (void)BN_GF2m_mod_solve_quad(r, a, p, ctx);

end:
  BN_CTX_free(ctx);
  BN_free(r);
  BN_free(b);
  BN_free(a);
  BN_free(p);
}

/* ---- 3: BIGNUM text ---------------------------------------------------------- */

static void mode_bntext(const uint8_t *data, size_t size) {
  harness_cur c = {data, size};
  unsigned kind = harness_u8(&c) % 3;
  size_t len = harness_u32(&c), i;
  char *text;
  BIGNUM *bn = NULL;

  if (c.left == 0)
    return;
  if (len < c.left)
    len = c.left;
  if (len > HARNESS_MAX_TEXT)
    len = HARNESS_MAX_TEXT;

  if ((text = malloc(len + 1)) == NULL)
    return;
  for (i = 0; i < len; i += c.left)
    memcpy(text + i, c.data, len - i < c.left ? len - i : c.left);
  text[len] = '\0';

  switch (kind) {
  case 0:
    (void)BN_hex2bn(&bn, text);
    break;
  case 1:
    (void)BN_dec2bn(&bn, text);
    break;
  default:
    (void)BN_asc2bn(&bn, text);
    break;
  }
  if (bn != NULL) {
    char *s = BN_bn2hex(bn);
    OPENSSL_free(s);
  }
  BN_free(bn);
  free(text);
}

/* ---- 4: streaming encoders --------------------------------------------------- */

static void mode_stream(const uint8_t *data, size_t size) {
  harness_cur c = {data, size};
  EVP_ENCODE_CTX *enc = EVP_ENCODE_CTX_new();
  EVP_ENCODE_CTX *dec = EVP_ENCODE_CTX_new();
  MDC2_CTX mdc2;
  unsigned char md[MDC2_DIGEST_LENGTH];
  unsigned char *obuf = NULL;
  void *zeros = MAP_FAILED;
  int outl;

  if (enc == NULL || dec == NULL)
    goto end;
  EVP_EncodeInit(enc);
  EVP_DecodeInit(dec);
  MDC2_Init(&mdc2);

  while (c.left > 0) {
    unsigned op = harness_u8(&c);
    size_t len = harness_u32(&c);
    const unsigned char *in;

    if (op & 0x80) {
      /* Large update backed by untouched anonymous memory (zero pages). */
      if (len > HARNESS_MAX_ZERO)
        len = HARNESS_MAX_ZERO;
      if (zeros == MAP_FAILED)
        zeros = mmap(NULL, HARNESS_MAX_ZERO, PROT_READ,
                     MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
      if (zeros == MAP_FAILED)
        break;
      in = zeros;
    } else {
      if (len > c.left)
        len = c.left;
      in = c.data;
      c.data += len;
      c.left -= len;
    }

    if (op & 1) {
      MDC2_Update(&mdc2, in, len);
    } else {
      /* Output is at most 65 bytes per 48 input bytes, plus a line. */
      free(obuf);
      obuf = malloc(len / 48 * 65 + 128);
      if (obuf == NULL)
        break;
      (void)EVP_EncodeUpdate(enc, obuf, &outl, in, (int)len);
    }

    if ((op & 2) && len <= 0x10000) {
      free(obuf);
      obuf = malloc(len + 128);
      if (obuf == NULL)
        break;
      (void)EVP_DecodeUpdate(dec, obuf, &outl, in, (int)len);
    }
  }

  if (obuf == NULL)
    obuf = malloc(128);
  if (obuf != NULL) {
    EVP_EncodeFinal(enc, obuf, &outl);
    (void)EVP_DecodeFinal(dec, obuf, &outl);
  }
  MDC2_Final(md, &mdc2);

end:
  if (zeros != MAP_FAILED)
    munmap(zeros, HARNESS_MAX_ZERO);
  free(obuf);
  EVP_ENCODE_CTX_free(dec);
  EVP_ENCODE_CTX_free(enc);
}

static int fuzz_one(const uint8_t *data, size_t size) {
  if (size < 1)
    return 0;
  switch (data[0] % 5) {
  case 0:
    mode_asn1(data + 1, size - 1);
    break;
  case 1:
    mode_pkcs7(data + 1, size - 1);
    break;
  case 2:
    mode_gf2m(data + 1, size - 1);
    break;
  case 3:
    mode_bntext(data + 1, size - 1);
    break;
  default:
    mode_stream(data + 1, size - 1);
    break;
  }
  ERR_clear_error();
  return 0;
}
