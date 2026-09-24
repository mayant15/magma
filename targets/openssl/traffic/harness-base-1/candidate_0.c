#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_0(uint8_t* data, int size) {
  uint8_t** in = &data;
  X509_STORE* null13 = NULL;
  X509_STORE_free(null13);
  traffic_assert(true);
  X509_STORE_CTX* var57 = X509_STORE_CTX_new();
  X509* null65 = NULL;
  X509_free(null65);
  traffic_assert(true);
}