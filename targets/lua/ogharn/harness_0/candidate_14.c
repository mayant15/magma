#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <lua.h>
#include <lauxlib.h>

static int function_pointer3458764515342024704fp_cand14(lua_State* arg0, int arg1, lua_KContext arg2){
	exit(0);
}

int fuzz_14(char* fuzzData, long size) {
   lua_KContext lua_pcallkvar4;
	memset(&lua_pcallkvar4, 0, sizeof(lua_pcallkvar4));

   lua_State* luaL_newstateval1 = luaL_newstate();
	if(!luaL_newstateval1){
		fprintf(stderr, "err");
		exit(0);	}
   int luaL_loadbufferxval1 = luaL_loadbufferx(luaL_newstateval1, fuzzData, size, NULL, NULL);
	if((int)luaL_loadbufferxval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int lua_pcallkval1 = lua_pcallk(luaL_newstateval1, LUA_TBOOLEAN, luaL_loadbufferxval1, luaL_loadbufferxval1, lua_pcallkvar4, function_pointer3458764515342024704fp_cand14);
	if((int)lua_pcallkval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int lua_gettopval1 = lua_gettop(luaL_newstateval1);
	if((int)lua_gettopval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   int lua_checkstackval1 = lua_checkstack(luaL_newstateval1, lua_pcallkval1);
	if((int)lua_checkstackval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
