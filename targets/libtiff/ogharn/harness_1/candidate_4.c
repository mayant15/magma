#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <tiffio.h>
#include <tiff-support.h>

int fuzz_4(char* fuzzData, long size) {
   TIFF* tiff_open_rval1 = tiff_open_r(fuzzData, TIFF_FUZZ_MAX_BUF);
	if(!tiff_open_rval1){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
