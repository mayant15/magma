#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_1(uint8_t* data, int size) {
  uint8_t** in = &data;
  X509_STORE_CTX* var28 = X509_STORE_CTX_new();
  X509* null36 = NULL;
  X509_free(null36);
  traffic_assert(true);
  int var86 = X509_STORE_CTX_get_error(var28);
  traffic_assert(true);
}