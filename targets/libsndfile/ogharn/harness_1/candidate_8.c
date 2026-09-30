#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sndfile.h>
#include <sndfile-support.h>

int fuzz_8(char* fuzzData, long size) {
   SNDFILE* sf_init_filevar2;
	memset(&sf_init_filevar2, 0, sizeof(sf_init_filevar2));

   VIO_DATA sf_init_filevar3;
	memset(&sf_init_filevar3, 0, sizeof(sf_init_filevar3));

   SF_VIRTUAL_IO sf_init_filevar4;
	memset(&sf_init_filevar4, 0, sizeof(sf_init_filevar4));

   SF_INFO sf_init_filevar5;
	memset(&sf_init_filevar5, 0, sizeof(sf_init_filevar5));

   int sf_init_fileval1 = sf_init_file(fuzzData, size, &sf_init_filevar2, &sf_init_filevar3, &sf_init_filevar4, &sf_init_filevar5);
	if((int)sf_init_fileval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int sf_fuzz_readf_doubleval1 = sf_fuzz_readf_double(sf_init_filevar2, 64);
	if((int)sf_fuzz_readf_doubleval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int sf_fuzz_readf_intval1 = sf_fuzz_readf_int(sf_init_filevar2, sf_fuzz_readf_doubleval1);
	if((int)sf_fuzz_readf_intval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
