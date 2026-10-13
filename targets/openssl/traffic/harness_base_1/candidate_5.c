#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_5(uint8_t* data, int size) {
  X509_STORE* var28 = X509_STORE_new();
  X509_STORE_CTX* var57 = X509_STORE_CTX_new();
  X509* null59 = NULL;
  X509_free(null59);
  traffic_assert(true);
  X509_STORE_free(var28);
  traffic_assert(true);
  int var144 = X509_STORE_CTX_get_error(var57);
  traffic_assert(true);
  x509_fuzz_ctx_cleanup(var57);
  traffic_assert(true);
  uint8_t* out191_slot; uint8_t** out191 = &out191_slot;
  X509* var203 = x509_fuzz_d2i_X509(data, size, out191);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const221 = 0;
  X509* var235 = x509_fuzz_d2i_X509(data, const221, out191);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  X509_free(var203);
  traffic_assert(true);
}