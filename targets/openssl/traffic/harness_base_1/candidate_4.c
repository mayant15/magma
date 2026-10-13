#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_4(uint8_t* data, int size) {
  X509_STORE* var28 = X509_STORE_new();
  X509_STORE_CTX* var57 = X509_STORE_CTX_new();
  X509* null59 = NULL;
  X509_free(null59);
  traffic_assert(true);
  X509_STORE_free(var28);
  traffic_assert(true);
  int var144 = X509_verify_cert(var57);
  traffic_assert(true);
  int var174 = X509_verify_cert(var57);
  traffic_assert(true);
  X509_STORE* null197 = NULL;
  X509* null199 = NULL;
  int var204 = x509_fuzz_ctx_init(var57, null197, null199);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  x509_fuzz_ctx_cleanup(var57);
  traffic_assert(true);
}