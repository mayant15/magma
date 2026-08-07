#include <traffic.h>

#include <openssl/ssl.h>

int LLVMFuzzerTestOneInput(uint8_t* data, int size) {
  SSL_METHOD* var2 = SSLv23_method();
  SSL_CTX* var5 = SSL_CTX_new(var2);
}