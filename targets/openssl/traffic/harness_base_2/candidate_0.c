#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_0(uint8_t* data, int size) {
  X509_STORE_CTX* var28 = X509_STORE_CTX_new();
  X509_STORE_CTX* null56 = NULL;
  x509_fuzz_ctx_free(null56);
  traffic_assert(true);
}