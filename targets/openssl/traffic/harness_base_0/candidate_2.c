#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_2(uint8_t* data, int size) {
  X509_STORE_CTX* null9 = NULL;
  int var28 = X509_verify_cert(null9);
  traffic_assert(true);
  uint8_t* out46_slot; uint8_t** out46 = &out46_slot;
  X509* var58 = x509_fuzz_d2i_X509(data, var28, out46);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}