#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_5(uint8_t* data, int size) {
  X509_STORE* var28 = X509_STORE_new();
  X509_STORE_CTX* var57 = X509_STORE_CTX_new();
  uint8_t* out74_slot; uint8_t** out74 = &out74_slot;
  X509* var86 = x509_fuzz_d2i_X509(data, size, out74);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  X509_STORE_CTX* null109 = NULL;
  int var118 = x509_fuzz_ctx_init(null109, var28, var86);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}