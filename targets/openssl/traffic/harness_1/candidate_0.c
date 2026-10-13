#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_0(uint8_t* data, int size) {
  X509_STORE_CTX* var12 = X509_STORE_CTX_new();
  if (!((var12 == NULL))) {
    traffic_assert(true);
    x509_fuzz_ctx_free(var12);
  } else if ((var12 == NULL)) {
  }
}