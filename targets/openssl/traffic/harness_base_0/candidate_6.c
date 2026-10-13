#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_6(uint8_t* data, int size) {
  X509_STORE* var28 = X509_STORE_new();
  X509_STORE_CTX* var57 = X509_STORE_CTX_new();
  X509_STORE_CTX* null85 = NULL;
  x509_fuzz_ctx_free(null85);
  traffic_assert(true);
  int var115 = X509_verify_cert(var57);
  traffic_assert(true);
  int var145 = X509_STORE_CTX_get_error(var57);
  traffic_assert(true);
  X509* null170 = NULL;
  int var175 = x509_fuzz_ctx_init(var57, var28, null170);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  x509_fuzz_ctx_free(var57);
  traffic_assert(true);
  uint8_t** null225 = NULL;
  X509* var236 = x509_fuzz_d2i_X509(data, var145, null225);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}