#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_1(uint8_t* data, int size) {
  uint8_t** in = &data;
  X509* null7 = NULL;
  X509_free(null7);
  traffic_assert(true);
  X509_STORE_CTX* null56 = NULL;
  x509_fuzz_ctx_free(null56);
  traffic_assert(true);
}