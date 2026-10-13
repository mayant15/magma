#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_1(uint8_t* data, int size) {
  X509_STORE* var28 = X509_STORE_new();
  X509_STORE_CTX* null48 = NULL;
  X509* null52 = NULL;
  int var57 = x509_fuzz_ctx_init(null48, var28, null52);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  X509_STORE* null68 = NULL;
  X509_STORE_free(null68);
  traffic_assert(true);
}