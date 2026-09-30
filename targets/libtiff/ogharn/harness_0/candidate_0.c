#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <tiffio.h>
#include <tiff-support.h>

int fuzz_0(char* fuzzData, long size) {
   TIFF* tiff_open_rval1 = tiff_open_r(fuzzData, size);
	if(!tiff_open_rval1){
		fprintf(stderr, "err");
		exit(0);	}
   int tiff_fuzz_read_rgbaval1 = tiff_fuzz_read_rgba(tiff_open_rval1);
	if((int)tiff_fuzz_read_rgbaval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   TIFFClose(tiff_open_rval1);
   return 0;
}
