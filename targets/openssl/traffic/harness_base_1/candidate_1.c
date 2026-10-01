#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_1(uint8_t* data, int size) {
  X509_STORE* null7 = NULL;
  X509_STORE_free(null7);
  traffic_assert(true);
  X509* null30 = NULL;
  X509_free(null30);
  traffic_assert(true);
}