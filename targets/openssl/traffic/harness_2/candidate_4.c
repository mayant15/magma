#include <traffic.h>

#include <openssl/x509.h>

#include <openssl/x509_vfy.h>

#include <x509-support.h>

int fuzz_4(uint8_t* data, int size) {
  X509_STORE_CTX* var12 = X509_STORE_CTX_new();
  if (!((var12 == NULL))) {
    traffic_assert(true);
    uint8_t* out22_slot; uint8_t** out22 = &out22_slot;
    X509* var27 = x509_fuzz_d2i_X509(data, size, out22);
    if (!((var27 == NULL))) {
      traffic_assert(true);
      X509_STORE* var39 = X509_STORE_new();
      if (!((var39 == NULL))) {
        traffic_assert(true);
        int var64 = x509_fuzz_ctx_init(var12, var39, var27);
        traffic_assert(true);
        traffic_assert(true);
        if ((var64 == 1)) {
          traffic_assert(true);
          x509_fuzz_ctx_cleanup(var12);
          traffic_assert(true);
        } else if (!((var64 == 1))) {
          traffic_assert(true);
        }
      } else if ((var39 == NULL)) {
      }
    } else if ((var27 == NULL)) {
      x509_fuzz_ctx_cleanup(var12);
      traffic_assert(true);
    }
  } else if ((var12 == NULL)) {
  }
}