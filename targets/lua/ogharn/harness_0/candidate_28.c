#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <lua.h>
#include <lauxlib.h>

int fuzz_28(char* fuzzData, long size) {
   lua_Integer lua_pushintegervar1;
	memset(&lua_pushintegervar1, 0, sizeof(lua_pushintegervar1));

   lua_State* luaL_newstateval1 = luaL_newstate();
	if(!luaL_newstateval1){
		fprintf(stderr, "err");
		exit(0);	}
   int luaL_loadbufferxval1 = luaL_loadbufferx(luaL_newstateval1, fuzzData, size, NULL, NULL);
	if((int)luaL_loadbufferxval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   lua_pushinteger(luaL_newstateval1, lua_pushintegervar1);
   char* lua_tolstringval1 = lua_tolstring(luaL_newstateval1, LUA_GCCOLLECT, NULL);
	if(!lua_tolstringval1){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
