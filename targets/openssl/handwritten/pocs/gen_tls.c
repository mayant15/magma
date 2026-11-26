/* Record a client transcript that harness_2 replays to a completed handshake.
 *
 * Runs a real OpenSSL client against harness_2's own server configuration
 * (same embedded identity, same deterministic RNG and clock) over memory
 * BIOs and writes  0x00 || <everything the client sent>  to argv[1].
 *
 *   ssl019.tls: TLS 1.0 + AES128-SHA. OpenSSL clients send an empty record
 *   before each application data record for CBC suites in TLS <= 1.0
 *   (SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS is not set), which the server's
 *   SSL_peek then sees as a zero-length record.
 *
 * Build (from targets/openssl/handwritten, against an installed OpenSSL):
 *   cc -I support -I $OUT/include pocs/gen_tls.c -o gen_tls \
 *      $OUT/lib/libssl.a $OUT/lib/libcrypto.a $OUT/magma.o -lpthread -ldl
 *   ./gen_tls ssl019.tls
 */

#define HARNESS_NO_MAIN
#include "../harness_2.c"

static BIO *transcript;

/* Move pending bytes from one endpoint's write BIO to the other's read BIO,
 * recording them if they come from the client. */
static void pump(BIO *from, BIO *to, int record) {
  char buf[4096];
  int n;
  while ((n = BIO_read(from, buf, sizeof buf)) > 0) {
    BIO_write(to, buf, n);
    if (record)
      BIO_write(transcript, buf, n);
  }
}

int main(int argc, char *argv[]) {
  SSL_CTX *sctx, *cctx;
  SSL *srv, *cli;
  BIO *s_in, *s_out, *c_in, *c_out;
  int i, cdone = 0, sdone = 0;
  char *p;
  long len;
  FILE *f;

  if (argc < 2)
    return 2;
  harness_set_rand();

  sctx = make_ctx(0);
  cctx = SSL_CTX_new(TLS_client_method());
  SSL_CTX_set_min_proto_version(cctx, TLS1_VERSION);
  SSL_CTX_set_max_proto_version(cctx, TLS1_VERSION);
  SSL_CTX_set_cipher_list(cctx, "AES128-SHA:@SECLEVEL=0");
  SSL_CTX_clear_options(cctx, SSL_OP_DONT_INSERT_EMPTY_FRAGMENTS);

  srv = SSL_new(sctx);
  cli = SSL_new(cctx);
  s_in = BIO_new(BIO_s_mem());
  s_out = BIO_new(BIO_s_mem());
  c_in = BIO_new(BIO_s_mem());
  c_out = BIO_new(BIO_s_mem());
  BIO_set_mem_eof_return(s_in, -1);
  BIO_set_mem_eof_return(c_in, -1);
  SSL_set_bio(srv, s_in, s_out);
  SSL_set_bio(cli, c_in, c_out);
  SSL_set_accept_state(srv);
  SSL_set_connect_state(cli);
  transcript = BIO_new(BIO_s_mem());

  for (i = 0; i < 32 && !(cdone && sdone); i++) {
    if (!cdone)
      cdone = SSL_do_handshake(cli) == 1;
    pump(c_out, s_in, 1);
    if (!sdone)
      sdone = SSL_do_handshake(srv) == 1;
    pump(s_out, c_in, 0);
  }
  if (!(cdone && sdone)) {
    ERR_print_errors_fp(stderr);
    return 1;
  }

  SSL_write(cli, "ping", 4);
  pump(c_out, s_in, 1);

  len = BIO_get_mem_data(transcript, &p);
  f = fopen(argv[1], "wb");
  if (f == NULL)
    return 1;
  fputc(0x00, f); /* harness_2: TLS */
  fwrite(p, 1, (size_t)len, f);
  fclose(f);
  fprintf(stderr, "wrote %ld transcript bytes, cipher %s, %s\n", len,
          SSL_get_cipher(cli), SSL_get_version(cli));
  return 0;
}
