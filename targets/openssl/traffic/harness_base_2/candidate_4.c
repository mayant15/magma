#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_4(uint8_t* data, int size) {
  X509_STORE_CTX* null27 = NULL;
  x509_fuzz_ctx_free(null27);
  traffic_assert(true);
  uint8_t* out45_slot; uint8_t** out45 = &out45_slot;
  X509* var57 = x509_fuzz_d2i_X509(data, size, out45);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  X509_free(var57);
  traffic_assert(true);
}