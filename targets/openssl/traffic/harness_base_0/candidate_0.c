#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_0(uint8_t* data, int size) {
  X509_STORE* var28 = X509_STORE_new();
  X509_STORE_CTX* var57 = X509_STORE_CTX_new();
  X509_STORE_CTX* null85 = NULL;
  x509_fuzz_ctx_free(null85);
  traffic_assert(true);
  int var115 = X509_verify_cert(var57);
  traffic_assert(true);
  X509_STORE_free(var28);
  traffic_assert(true);
}