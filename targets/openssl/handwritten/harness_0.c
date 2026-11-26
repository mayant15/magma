/* X.509 certificate consumer.
 *
 * Input is a stream of DER objects read through a memory BIO, the way
 * applications load a certificate bundle from a file or socket:
 *
 *   Certificate [CRL ...]
 *
 * The certificate is printed, re-encoded as a request, self-verified, and
 * finally run through X509_verify_cert with CRL checking against the CRLs
 * that follow it. A verify callback that accepts every error (as monitoring
 * / inventory tools do) keeps chain verification going past untrusted or
 * expired certificates so the revocation stage is still reached.
 *
 *   SSL003  DER header claims more bytes than the stream has (d2i_*_bio)
 *   SSL004  X509_NAME_oneline (canary only compiled on CHARSET_EBCDIC hosts)
 *   SSL009  sbgp-ipAddrBlock with a 1-byte addressFamily (X509_print)
 *   SSL012  certificate whose public key cannot be decoded
 *   SSL013  RSA-PSS signature with malformed parameters, verified with a
 *           legacy (RSA*-backed) key as pre-3.0 API users do
 *   SSL014  signature AlgorithmIdentifier whose parameters are a BOOLEAN
 *   SSL017  a CRL that scores 0 for the certificate under X509_V_FLAG_CRL_CHECK
 */

/* EVP_PKEY_get1_RSA / EVP_PKEY_set1_RSA: legacy key API. */
#define OPENSSL_SUPPRESS_DEPRECATED

#include "harness.h"

#include <openssl/rsa.h>
#include <openssl/x509v3.h>

#define MAX_CRLS 8

static int accept_all(int ok, X509_STORE_CTX *ctx) {
  (void)ok;
  (void)ctx;
  return 1;
}

/* Re-wrap an RSA public key the way code written against the 1.1 API does
 * (RSA* + EVP_PKEY_set1_RSA). Such keys are "legacy" EVP_PKEYs and take the
 * EVP_PKEY_ASN1_METHOD item_verify path for RSA-PSS signatures. */
static EVP_PKEY *legacy_rsa_copy(EVP_PKEY *pk) {
  RSA *rsa;
  EVP_PKEY *lk;

  if (pk == NULL || EVP_PKEY_get_base_id(pk) != EVP_PKEY_RSA)
    return NULL;
  rsa = EVP_PKEY_get1_RSA(pk);
  lk = EVP_PKEY_new();
  if (rsa == NULL || lk == NULL || !EVP_PKEY_set1_RSA(lk, rsa)) {
    EVP_PKEY_free(lk);
    lk = NULL;
  }
  RSA_free(rsa);
  return lk;
}

static void verify_chain(X509 *x, STACK_OF(X509_CRL) *crls) {
  X509_STORE *store = X509_STORE_new();
  X509_STORE_CTX *ctx = X509_STORE_CTX_new();

  if (store == NULL || ctx == NULL)
    goto end;

  /* The certificate is its own trust anchor (PARTIAL_CHAIN), so every input
   * reaches the revocation stage regardless of issuer. */
  X509_STORE_add_cert(store, x);
  X509_STORE_set_flags(store, X509_V_FLAG_CRL_CHECK | X509_V_FLAG_CRL_CHECK_ALL |
                                  X509_V_FLAG_PARTIAL_CHAIN |
                                  X509_V_FLAG_EXTENDED_CRL_SUPPORT |
                                  X509_V_FLAG_USE_DELTAS);
  X509_STORE_set_verify_cb(store, accept_all);

  if (X509_STORE_CTX_init(ctx, store, x, NULL) != 1)
    goto end;
  X509_STORE_CTX_set0_crls(ctx, crls);
  X509_STORE_CTX_set_time(ctx, 0, HARNESS_TIME);
  (void)X509_verify_cert(ctx);

end:
  X509_STORE_CTX_free(ctx);
  X509_STORE_free(store);
}

static int fuzz_one(const uint8_t *data, size_t size) {
  BIO *in, *out;
  X509 *x;
  X509_CRL *crl;
  X509_REQ *req;
  EVP_PKEY *lk;
  STACK_OF(X509_CRL) *crls;
  char buf[256];
  int i;

  in = BIO_new_mem_buf(data, (int)size);
  if (in == NULL)
    return 0;

  x = d2i_X509_bio(in, NULL);
  if (x == NULL) {
    BIO_free(in);
    ERR_clear_error();
    return 0;
  }

  crls = sk_X509_CRL_new_null();
  for (i = 0; crls != NULL && i < MAX_CRLS && BIO_pending(in) > 0; i++) {
    crl = d2i_X509_CRL_bio(in, NULL);
    if (crl == NULL)
      break;
    if (!sk_X509_CRL_push(crls, crl))
      X509_CRL_free(crl);
  }
  BIO_free(in);

  /* Pretty printing: walks every extension through its i2r/i2v method. */
  out = BIO_new(BIO_s_null());
  X509_print(out, x);
  for (i = 0; i < sk_X509_CRL_num(crls); i++)
    X509_CRL_print(out, sk_X509_CRL_value(crls, i));
  BIO_free(out);

  X509_NAME_oneline(X509_get_subject_name(x), buf, sizeof buf);
  X509_NAME_oneline(X509_get_issuer_name(x), buf, sizeof buf);

  /* Self-signature check (also compares the inner and outer signature
   * AlgorithmIdentifiers). */
  (void)X509_verify(x, X509_get0_pubkey(x));
  if ((lk = legacy_rsa_copy(X509_get0_pubkey(x))) != NULL) {
    (void)X509_verify(x, lk);
    EVP_PKEY_free(lk);
  }

  /* Turn the certificate back into a CSR, as `openssl x509 -x509toreq`. */
  req = X509_to_X509_REQ(x, NULL, NULL);
  X509_REQ_free(req);

  verify_chain(x, crls);

  sk_X509_CRL_pop_free(crls, X509_CRL_free);
  X509_free(x);
  ERR_clear_error();
  return 0;
}
