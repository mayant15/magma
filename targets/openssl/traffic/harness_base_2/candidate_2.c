#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_2(uint8_t* data, int size) {
  X509_STORE_CTX* null27 = NULL;
  x509_fuzz_ctx_free(null27);
  traffic_assert(true);
  X509_STORE* null50 = NULL;
  X509* null52 = NULL;
  int var57 = x509_fuzz_ctx_init(null27, null50, null52);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  X509_STORE* var89 = X509_STORE_new();
  X509_STORE_free(var89);
  traffic_assert(true);
}