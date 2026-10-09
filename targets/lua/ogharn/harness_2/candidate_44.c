#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <lua.h>
#include <lauxlib.h>

int fuzz_44(char* fuzzData, long size) {
   lua_Integer lua_pushintegervar1;
	memset(&lua_pushintegervar1, 0, sizeof(lua_pushintegervar1));

   lua_State* luaL_newstateval1 = luaL_newstate();
	if(!luaL_newstateval1){
		fprintf(stderr, "err");
		exit(0);	}
   int luaL_loadbufferxval1 = luaL_loadbufferx(luaL_newstateval1, fuzzData, size, fuzzData+size, fuzzData);
	if((int)luaL_loadbufferxval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   lua_settop(luaL_newstateval1, LUA_GCINC);
   lua_pushinteger(luaL_newstateval1, lua_pushintegervar1);
   return 0;
}
