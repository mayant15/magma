#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>
#include <png-support.h>

int fuzz_4(char* fuzzData, long size) {
   png_imagep png_fuzz_new_imageval1 = png_fuzz_new_image();
   int png_image_begin_read_from_memoryval1 = png_image_begin_read_from_memory(png_fuzz_new_imageval1, (void*)fuzzData, size);
	if((int)png_image_begin_read_from_memoryval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int png_image_finish_readval1 = png_image_finish_read(png_fuzz_new_imageval1, NULL, (void*)&fuzzData, PNG_FP_MIN, NULL);
	if((int)png_image_finish_readval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
