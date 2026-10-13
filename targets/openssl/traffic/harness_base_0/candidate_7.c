#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_7(uint8_t* data, int size) {
  X509_STORE* var28 = X509_STORE_new();
  X509_STORE_CTX* var57 = X509_STORE_CTX_new();
  uint8_t* out74_slot; uint8_t** out74 = &out74_slot;
  X509* var86 = x509_fuzz_d2i_X509(data, size, out74);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var118 = X509_STORE_add_cert(var28, var86);
  traffic_assert(true);
  traffic_assert(true);
  X509_free(var86);
  traffic_assert(true);
  X509_free(var86);
  traffic_assert(true);
}