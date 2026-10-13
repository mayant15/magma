#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_1(uint8_t* data, int size) {
  X509_STORE_CTX* null9 = NULL;
  int var28 = X509_verify_cert(null9);
  traffic_assert(true);
  X509_STORE* null37 = NULL;
  X509_STORE_free(null37);
  traffic_assert(true);
}