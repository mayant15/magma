#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_0(uint8_t* data, int size) {
  uint8_t** in = &data;
  X509_STORE_CTX* null27 = NULL;
  x509_fuzz_ctx_free(null27);
  traffic_assert(true);
  X509_STORE* null42 = NULL;
  X509_STORE_free(null42);
  traffic_assert(true);
}