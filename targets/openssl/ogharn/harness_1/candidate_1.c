#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <openssl/x509.h>
#include <openssl/x509_vfy.h>
#include <x509-support.h>

int fuzz_1(char* fuzzData, long size) {
   X509* d2i_X509var0;
	memset(&d2i_X509var0, 0, sizeof(d2i_X509var0));

   X509* d2i_X509val1 = d2i_X509(&d2i_X509var0, &fuzzData, size);
	if(!d2i_X509val1){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
