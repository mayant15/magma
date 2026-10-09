#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <lua.h>
#include <lauxlib.h>

static int function_pointer3458764515342024704fp_cand50(lua_State* arg0, int arg1, lua_KContext arg2){
	exit(0);
}

int fuzz_50(char* fuzzData, long size) {
   char* luaL_loadbufferxvar4[size+1];
	sprintf(luaL_loadbufferxvar4, "/tmp/8m0hv");
   lua_KContext lua_pcallkvar4;
	memset(&lua_pcallkvar4, 0, sizeof(lua_pcallkvar4));

   size_t lua_tolstringvar2 = 1;
   lua_State* luaL_newstateval1 = luaL_newstate();
	if(!luaL_newstateval1){
		fprintf(stderr, "err");
		exit(0);	}
   int luaL_loadbufferxval1 = luaL_loadbufferx(luaL_newstateval1, fuzzData, size, fuzzData+size, luaL_loadbufferxvar4);
	if((int)luaL_loadbufferxval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int lua_pcallkval1 = lua_pcallk(luaL_newstateval1, LUA_GCSTOP, luaL_loadbufferxval1, LUA_OPSHR, lua_pcallkvar4, function_pointer3458764515342024704fp_cand50);
	if((int)lua_pcallkval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   char* lua_tolstringval1 = lua_tolstring(luaL_newstateval1, LUA_TNONE, &lua_tolstringvar2);
	if(!lua_tolstringval1){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
