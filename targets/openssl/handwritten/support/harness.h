/* Shared plumbing for the hand-written OpenSSL harnesses.
 *
 * Each harness defines `static int fuzz_one(const uint8_t *, size_t)`; this
 * header supplies a file-reading main() (AFL `@@` style, matching the traffic
 * and ogharn harnesses) plus:
 *
 *  - a deterministic, stateless RNG provider and a fixed time(), the same
 *    approach as OpenSSL's own fuzz/server.c (FuzzerSetRand / FUZZTIME), so
 *    that a recorded TLS transcript replays bit-for-bit: the server random,
 *    session id and key schedule are a function of the input alone. The
 *    RNG can be told to fail its N-th request (fault injection);
 *  - the embedded test RSA key / certificate (keys.h);
 *  - a tiny byte cursor for harness-level configuration.
 */

#ifndef OPENSSL_HANDWRITTEN_HARNESS_H
#define OPENSSL_HANDWRITTEN_HARNESS_H

#include <openssl/bio.h>
#include <openssl/core_dispatch.h>
#include <openssl/core_names.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/provider.h>
#include <openssl/rand.h>
#include <openssl/x509.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "keys.h"

/* ---- fixed clock ---------------------------------------------------------- */

/* 2021-01-01T00:00:00Z: inside the validity of the embedded certificate. */
#define HARNESS_TIME ((time_t)1609459200)

time_t time(time_t *t) {
  if (t != NULL)
    *t = HARNESS_TIME;
  return HARNESS_TIME;
}

/* ---- deterministic RNG ---------------------------------------------------- */

/* Every request returns 0x01 0x02 0x03 ...: no state, so the bytes a party
 * receives do not depend on how many other calls were made before it (this
 * lets pocs/gen_tls.c run a real client in the same process).
 *
 * Fault injection: if harness_rand_fail_at is N > 0, the N-th generate
 * request fails, as an exhausted / broken entropy source would. Harnesses
 * take N from the input to exercise error handling after RNG failure. */

static unsigned harness_rand_calls, harness_rand_fail_at;

static void *hrand_newctx(void *provctx, void *parent,
                          const OSSL_DISPATCH *parent_dispatch) {
  int *st = OPENSSL_malloc(sizeof(*st));
  (void)provctx;
  (void)parent;
  (void)parent_dispatch;
  if (st != NULL)
    *st = EVP_RAND_STATE_UNINITIALISED;
  return st;
}

static void hrand_freectx(void *vrng) { OPENSSL_free(vrng); }

static int hrand_instantiate(void *vrng, unsigned int strength, int pr,
                             const unsigned char *pstr, size_t pstr_len,
                             const OSSL_PARAM params[]) {
  (void)strength;
  (void)pr;
  (void)pstr;
  (void)pstr_len;
  (void)params;
  *(int *)vrng = EVP_RAND_STATE_READY;
  return 1;
}

static int hrand_uninstantiate(void *vrng) {
  *(int *)vrng = EVP_RAND_STATE_UNINITIALISED;
  return 1;
}

static int hrand_generate(void *vrng, unsigned char *out, size_t outlen,
                          unsigned int strength, int pr,
                          const unsigned char *adin, size_t adinlen) {
  size_t i;
  (void)vrng;
  (void)strength;
  (void)pr;
  (void)adin;
  (void)adinlen;
  if (++harness_rand_calls == harness_rand_fail_at)
    return 0;
  for (i = 0; i < outlen; i++)
    out[i] = (unsigned char)(i + 1);
  return 1;
}

static int hrand_enable_locking(void *vrng) {
  (void)vrng;
  return 1;
}

static int hrand_get_ctx_params(void *vrng, OSSL_PARAM params[]) {
  OSSL_PARAM *p;

  p = OSSL_PARAM_locate(params, OSSL_RAND_PARAM_STATE);
  if (p != NULL && !OSSL_PARAM_set_int(p, *(int *)vrng))
    return 0;
  p = OSSL_PARAM_locate(params, OSSL_RAND_PARAM_STRENGTH);
  if (p != NULL && !OSSL_PARAM_set_int(p, 500))
    return 0;
  p = OSSL_PARAM_locate(params, OSSL_RAND_PARAM_MAX_REQUEST);
  if (p != NULL && !OSSL_PARAM_set_size_t(p, INT_MAX))
    return 0;
  return 1;
}

static const OSSL_PARAM *hrand_gettable_ctx_params(void *vrng, void *provctx) {
  static const OSSL_PARAM known[] = {
      OSSL_PARAM_int(OSSL_RAND_PARAM_STATE, NULL),
      OSSL_PARAM_uint(OSSL_RAND_PARAM_STRENGTH, NULL),
      OSSL_PARAM_size_t(OSSL_RAND_PARAM_MAX_REQUEST, NULL), OSSL_PARAM_END};
  (void)vrng;
  (void)provctx;
  return known;
}

static const OSSL_DISPATCH hrand_functions[] = {
    {OSSL_FUNC_RAND_NEWCTX, (void (*)(void))hrand_newctx},
    {OSSL_FUNC_RAND_FREECTX, (void (*)(void))hrand_freectx},
    {OSSL_FUNC_RAND_INSTANTIATE, (void (*)(void))hrand_instantiate},
    {OSSL_FUNC_RAND_UNINSTANTIATE, (void (*)(void))hrand_uninstantiate},
    {OSSL_FUNC_RAND_GENERATE, (void (*)(void))hrand_generate},
    {OSSL_FUNC_RAND_ENABLE_LOCKING, (void (*)(void))hrand_enable_locking},
    {OSSL_FUNC_RAND_GETTABLE_CTX_PARAMS,
     (void (*)(void))hrand_gettable_ctx_params},
    {OSSL_FUNC_RAND_GET_CTX_PARAMS, (void (*)(void))hrand_get_ctx_params},
    {0, NULL}};

static const OSSL_ALGORITHM hrand_algs[] = {
    {"harness", "provider=harness-rand", hrand_functions, NULL},
    {NULL, NULL, NULL, NULL}};

static const OSSL_ALGORITHM *hrand_query(void *provctx, int operation_id,
                                         int *no_cache) {
  (void)provctx;
  *no_cache = 0;
  return operation_id == OSSL_OP_RAND ? hrand_algs : NULL;
}

static const OSSL_DISPATCH hrand_provider[] = {
    {OSSL_FUNC_PROVIDER_QUERY_OPERATION, (void (*)(void))hrand_query},
    {0, NULL}};

static int hrand_provider_init(const OSSL_CORE_HANDLE *handle,
                               const OSSL_DISPATCH *in,
                               const OSSL_DISPATCH **out, void **provctx) {
  (void)handle;
  (void)in;
  *provctx = NULL;
  *out = hrand_provider;
  return 1;
}

static inline void harness_set_rand(void) {
  if (!OSSL_PROVIDER_add_builtin(NULL, "harness-rand", hrand_provider_init) ||
      !RAND_set_DRBG_type(NULL, "harness", NULL, NULL, NULL) ||
      OSSL_PROVIDER_try_load(NULL, "harness-rand", 1) == NULL)
    exit(1);
}

/* ---- embedded identity ---------------------------------------------------- */

static inline EVP_PKEY *harness_load_key(void) {
  BIO *b = BIO_new_mem_buf(harness_key_pem, -1);
  EVP_PKEY *k = PEM_read_bio_PrivateKey(b, NULL, NULL, NULL);
  BIO_free(b);
  return k;
}

static inline X509 *harness_load_cert(void) {
  BIO *b = BIO_new_mem_buf(harness_cert_pem, -1);
  X509 *x = PEM_read_bio_X509(b, NULL, NULL, NULL);
  BIO_free(b);
  return x;
}

/* ---- input cursor --------------------------------------------------------- */

typedef struct {
  const uint8_t *data;
  size_t left;
} harness_cur;

static inline unsigned harness_u8(harness_cur *c) {
  unsigned v;
  if (c->left == 0)
    return 0;
  v = *c->data++;
  c->left--;
  return v;
}

static inline uint32_t harness_u32(harness_cur *c) {
  uint32_t v = 0;
  int i;
  for (i = 0; i < 4; i++)
    v = (v << 8) | harness_u8(c);
  return v;
}

/* Take a big-endian 16-bit length-prefixed slice (clamped to what is left). */
static inline harness_cur harness_slice16(harness_cur *c) {
  harness_cur s;
  size_t n = (size_t)harness_u8(c) << 8;
  n |= harness_u8(c);
  if (n > c->left)
    n = c->left;
  s.data = c->data;
  s.left = n;
  c->data += n;
  c->left -= n;
  return s;
}

/* ---- main ----------------------------------------------------------------- */

static int fuzz_one(const uint8_t *data, size_t size);

#ifndef HARNESS_NO_MAIN
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

  ret = fuzz_one(buf, (size_t)size);
  free(buf);
  return ret;
}
#endif

#endif /* OPENSSL_HANDWRITTEN_HARNESS_H */
