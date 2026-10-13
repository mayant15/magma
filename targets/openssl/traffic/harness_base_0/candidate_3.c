#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_3(uint8_t* data, int size) {
  X509_STORE* var28 = X509_STORE_new();
  X509_STORE_CTX* var57 = X509_STORE_CTX_new();
  uint8_t* out74_slot; uint8_t** out74 = &out74_slot;
  X509* var86 = x509_fuzz_d2i_X509(data, size, out74);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  x509_fuzz_ctx_cleanup(var57);
  traffic_assert(true);
  int const133 = 1;
  X509* var147 = x509_fuzz_d2i_X509(data, const133, out74);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}