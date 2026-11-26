/* TLS / DTLS server.
 *
 * byte 0, bit 0: 0 = TLS (any version, SSLv3 .. TLS 1.3), 1 = DTLS.
 * The rest is everything the client sends, fed through a read-only memory
 * BIO; what the server writes is discarded. RNG and clock are deterministic
 * (support/harness.h), so a recorded client transcript replays exactly.
 *
 * The server uses the embedded RSA identity, accepts every cipher suite
 * (including NULL and anonymous ones, as OpenSSL's fuzz/server.c does), and
 * after the handshake reads application data the way protocol sniffers /
 * proxies do: SSL_peek first, then SSL_read the same bytes.
 *
 *   SSL002  ClientHello larger than the initial 16 KiB handshake buffer
 *   SSL005  TLS 1.3 ClientHello / HelloRetryRequest / ClientHello, both with
 *           an OCSP status_request carrying responder ids
 *   SSL018  DTLS handshake fragment header with msg_len > max message size
 *   SSL019  zero-length application data record (e.g. the empty CBC fragment
 *           a TLS 1.0 OpenSSL client sends before data) seen by SSL_peek
 *   SSL020  TLS 1.2 SessionTicket of 48..64 bytes with the server's key name
 */

#include "harness.h"

#include <openssl/ssl.h>

#define MAX_APP_READS 64

static SSL_CTX *make_ctx(int dtls) {
  SSL_CTX *ctx;
  EVP_PKEY *key;
  X509 *cert;

  ctx = SSL_CTX_new(dtls ? DTLS_server_method() : TLS_server_method());
  if (ctx == NULL)
    return NULL;

  key = harness_load_key();
  cert = harness_load_cert();
  if (key == NULL || cert == NULL || !SSL_CTX_use_certificate(ctx, cert) ||
      !SSL_CTX_use_PrivateKey(ctx, key)) {
    SSL_CTX_free(ctx);
    ctx = NULL;
    goto end;
  }

  SSL_CTX_set_min_proto_version(ctx, 0);
  SSL_CTX_set_max_proto_version(ctx, 0);
  SSL_CTX_set_cipher_list(ctx, "ALL:eNULL:@SECLEVEL=0");
  SSL_CTX_set_options(ctx, SSL_OP_ALLOW_UNSAFE_LEGACY_RENEGOTIATION);
  if (dtls)
    SSL_CTX_set_options(ctx, SSL_OP_NO_QUERY_MTU);

end:
  X509_free(cert);
  EVP_PKEY_free(key);
  return ctx;
}

static int fuzz_one(const uint8_t *data, size_t size) {
  SSL_CTX *ctx;
  SSL *ssl;
  BIO *in, *out;
  int dtls, i, n;
  char buf[4096];

  if (size < 1)
    return 0;
  dtls = data[0] & 1;

  harness_set_rand();

  if ((ctx = make_ctx(dtls)) == NULL)
    return 0;
  ssl = SSL_new(ctx);
  in = BIO_new_mem_buf(data + 1, (int)(size - 1));
  out = BIO_new(BIO_s_mem());
  if (ssl == NULL || in == NULL || out == NULL) {
    BIO_free(in);
    BIO_free(out);
    goto end;
  }
  SSL_set_bio(ssl, in, out);
  if (dtls)
    SSL_set_mtu(ssl, 1500);
  SSL_set_accept_state(ssl);

  if (SSL_do_handshake(ssl) == 1) {
    for (i = 0; i < MAX_APP_READS; i++) {
      n = SSL_peek(ssl, buf, sizeof buf);
      if (n <= 0 && SSL_get_error(ssl, n) != SSL_ERROR_ZERO_RETURN &&
          SSL_get_error(ssl, n) != SSL_ERROR_WANT_READ)
        break;
      n = SSL_read(ssl, buf, sizeof buf);
      if (n <= 0)
        break;
    }
  }

end:
#ifdef HARNESS_DEBUG
  ERR_print_errors_fp(stderr);
#endif
  SSL_free(ssl);
  SSL_CTX_free(ctx);
  ERR_clear_error();
  return 0;
}
