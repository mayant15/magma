#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_1(uint8_t* data, int size) {
  uint8_t* out8_slot; uint8_t** out8 = &out8_slot;
  X509* var12 = x509_fuzz_d2i_X509(data, size, out8);
  if (!((var12 == NULL))) {
    traffic_assert(true);
    X509_free(var12);
  } else if ((var12 == NULL)) {
    X509_STORE* var23 = X509_STORE_new();
    if (!((var23 == NULL))) {
      traffic_assert(true);
      X509_STORE_free(var23);
    } else if ((var23 == NULL)) {
    }
  }
}