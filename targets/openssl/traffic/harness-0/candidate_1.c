#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

int fuzz_1(uint8_t* data, int size) {
  uint8_t** in = &data;
  X509_STORE* var12 = X509_STORE_new();
}