#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

int fuzz_0(uint8_t* data, int size) {
  uint8_t** in = &data;
  X509_STORE_CTX* var12 = X509_STORE_CTX_new();
}