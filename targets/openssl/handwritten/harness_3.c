/* TLS / DTLS client.
 *
 * byte 0, bit 0:    0 = TLS, 1 = DTLS
 * byte 0, bits 1-7: N > 0 makes the N-th RNG request fail (fault injection,
 *                   see support/harness.h); 0 = RNG never fails
 * The rest is everything the server sends, fed through a read-only memory
 * BIO; the client's own output is discarded. The client offers every cipher
 * suite including anonymous (EC)DH ones, does not verify the server (the
 * default SSL_VERIFY_NONE), and exchanges a little application data after
 * the handshake.
 *
 *   SSL008  client key exchange for DHE / ECDHE when generating the client's
 *           ephemeral key fails (here: RNG failure during key generation)
 */

#include "harness.h"

#include <openssl/ssl.h>

#define MAX_APP_READS 64

static int fuzz_one(const uint8_t *data, size_t size) {
  SSL_CTX *ctx = NULL;
  SSL *ssl = NULL;
  BIO *in, *out;
  int dtls, i;
  char buf[4096];

  if (size < 1)
    return 0;
  dtls = data[0] & 1;

  harness_set_rand();

  ctx = SSL_CTX_new(dtls ? DTLS_client_method() : TLS_client_method());
  if (ctx == NULL)
    return 0;
  SSL_CTX_set_min_proto_version(ctx, 0);
  SSL_CTX_set_max_proto_version(ctx, 0);
  SSL_CTX_set_cipher_list(ctx, "ALL:eNULL:@SECLEVEL=0");
  if (dtls)
    SSL_CTX_set_options(ctx, SSL_OP_NO_QUERY_MTU);

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
  SSL_set_tlsext_host_name(ssl, "localhost");
  SSL_set_connect_state(ssl);

  /* Arm fault injection only now: setup above must not be what fails. */
  harness_rand_calls = 0;
  harness_rand_fail_at = data[0] >> 1;

  if (SSL_do_handshake(ssl) == 1) {
    (void)SSL_write(ssl, "GET / HTTP/1.0\r\n\r\n", 18);
    for (i = 0; i < MAX_APP_READS; i++)
      if (SSL_read(ssl, buf, sizeof buf) <= 0)
        break;
  }

end:
#ifdef HARNESS_DEBUG
  ERR_print_errors_fp(stderr);
#endif
  harness_rand_fail_at = 0;
  SSL_free(ssl);
  SSL_CTX_free(ctx);
  ERR_clear_error();
  return 0;
}
