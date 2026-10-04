#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <lua.h>
#include <lauxlib.h>

int fuzz_19(char* fuzzData, long size) {
   lua_State* luaL_newstateval1 = luaL_newstate();
	if(!luaL_newstateval1){
		fprintf(stderr, "err");
		exit(0);	}
   int luaL_loadbufferxval1 = luaL_loadbufferx(luaL_newstateval1, fuzzData, size, "r", fuzzData);
	if((int)luaL_loadbufferxval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   lua_pushboolean(luaL_newstateval1, luaL_loadbufferxval1);
   return 0;
}
