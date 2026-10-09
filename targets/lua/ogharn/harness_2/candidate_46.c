#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <lua.h>
#include <lauxlib.h>

int fuzz_46(char* fuzzData, long size) {
   char* luaL_loadbufferxvar4[size+1];
	sprintf(luaL_loadbufferxvar4, "/tmp/yf0yi");
   lua_State* luaL_newstateval1 = luaL_newstate();
	if(!luaL_newstateval1){
		fprintf(stderr, "err");
		exit(0);	}
   int luaL_loadbufferxval1 = luaL_loadbufferx(luaL_newstateval1, fuzzData, size, fuzzData+size, luaL_loadbufferxvar4);
	if((int)luaL_loadbufferxval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int lua_gettopval1 = lua_gettop(luaL_newstateval1);
	if((int)lua_gettopval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
