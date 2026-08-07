#include <traffic.h>

#include <openssl/ssl.h>

int LLVMFuzzerTestOneInput(uint8_t* data, int size) {
  SSL_METHOD* null1 = NULL;
  SSL_CTX* var2 = SSL_CTX_new(null1);
  SSL_METHOD* var5 = SSLv23_method();
  SSL_METHOD* null7 = NULL;
  SSL_CTX* var8 = SSL_CTX_new(null7);
}