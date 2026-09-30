#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sqlite3.h>

int fuzz_4(char* fuzzData, long size) {
   sqlite3* sqlite3_openvar1;
	memset(&sqlite3_openvar1, 0, sizeof(sqlite3_openvar1));

   sqlite3_stmt* sqlite3_prepare_v2var3;
	memset(&sqlite3_prepare_v2var3, 0, sizeof(sqlite3_prepare_v2var3));

   int sqlite3_openval1 = sqlite3_open(":memory:", &sqlite3_openvar1);
	if((int)sqlite3_openval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int sqlite3_prepare_v2val1 = sqlite3_prepare_v2(sqlite3_openvar1, fuzzData, size, &sqlite3_prepare_v2var3, NULL);
	if((int)sqlite3_prepare_v2val1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int sqlite3_stepval1 = sqlite3_step(sqlite3_prepare_v2var3);
	if((int)sqlite3_stepval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int sqlite3_finalizeval1 = sqlite3_finalize(sqlite3_prepare_v2var3);
	if((int)sqlite3_finalizeval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
