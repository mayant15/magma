#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_6(uint8_t* data, int size) {
  X509_STORE_CTX* var28 = X509_STORE_CTX_new();
  uint8_t* null42 = NULL;
  int const43 = 0;
  uint8_t* out45_slot; uint8_t** out45 = &out45_slot;
  X509* var57 = x509_fuzz_d2i_X509(null42, const43, out45);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var89 = X509_STORE_CTX_get_error(var28);
  traffic_assert(true);
  int var119 = X509_verify_cert(var28);
  traffic_assert(true);
  x509_fuzz_ctx_cleanup(var28);
  traffic_assert(true);
  X509_STORE* null171 = NULL;
  int var178 = x509_fuzz_ctx_init(var28, null171, var57);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  x509_fuzz_ctx_free(var28);
  traffic_assert(true);
}