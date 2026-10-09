#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <lua.h>
#include <lauxlib.h>

static int function_pointer3458764515342024704fp_cand34(lua_State* arg0, int arg1, lua_KContext arg2){
	exit(0);
}

int fuzz_34(char* fuzzData, long size) {
   char* luaL_loadbufferxvar4[size+1];
	sprintf(luaL_loadbufferxvar4, "/tmp/p4lv0");
   lua_KContext lua_pcallkvar4;
	memset(&lua_pcallkvar4, 0, sizeof(lua_pcallkvar4));

   lua_Integer lua_pushintegervar1;
	memset(&lua_pushintegervar1, 0, sizeof(lua_pushintegervar1));

   lua_State* luaL_newstateval1 = luaL_newstate();
	if(!luaL_newstateval1){
		fprintf(stderr, "err");
		exit(0);	}
   int luaL_loadbufferxval1 = luaL_loadbufferx(luaL_newstateval1, fuzzData, size, fuzzData+size, luaL_loadbufferxvar4);
	if((int)luaL_loadbufferxval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int lua_pcallkval1 = lua_pcallk(luaL_newstateval1, LUA_OPEQ, luaL_loadbufferxval1, LUA_MINSTACK, lua_pcallkvar4, function_pointer3458764515342024704fp_cand34);
	if((int)lua_pcallkval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   char* lua_tolstringval1 = lua_tolstring(luaL_newstateval1, 1, NULL);
	if(!lua_tolstringval1){
		fprintf(stderr, "err");
		exit(0);	}
   lua_pushinteger(luaL_newstateval1, lua_pushintegervar1);
   return 0;
}
