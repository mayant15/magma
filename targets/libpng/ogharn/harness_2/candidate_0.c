#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>
#include <png-support.h>

int fuzz_0(char* fuzzData, long size) {
   png_const_colorp png_image_finish_readvar1;
	memset(&png_image_finish_readvar1, 0, sizeof(png_image_finish_readvar1));

   void* png_image_finish_readvar2[size+1];
	sprintf(png_image_finish_readvar2, "/tmp/ex06f");
   png_int_32 png_image_finish_readvar3;
	memset(&png_image_finish_readvar3, 0, sizeof(png_image_finish_readvar3));

   png_imagep png_fuzz_new_imageval1 = png_fuzz_new_image();
   int png_image_begin_read_from_memoryval1 = png_image_begin_read_from_memory(png_fuzz_new_imageval1, (void*)fuzzData, size);
	if((int)png_image_begin_read_from_memoryval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int png_image_finish_readval1 = png_image_finish_read(png_fuzz_new_imageval1, png_image_finish_readvar1, png_image_finish_readvar2, png_image_finish_readvar3, (void*)&fuzzData);
	if((int)png_image_finish_readval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
