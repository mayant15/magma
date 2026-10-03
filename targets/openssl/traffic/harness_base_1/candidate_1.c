#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_1(uint8_t* data, int size) {
  X509* null1 = NULL;
  X509_free(null1);
  traffic_assert(true);
  X509_STORE_CTX* var57 = X509_STORE_CTX_new();
  X509_STORE* null65 = NULL;
  X509_STORE_free(null65);
  traffic_assert(true);
}