#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <lua.h>
#include <lauxlib.h>

int fuzz_13(char* fuzzData, long size) {
   char* luaL_loadbufferxvar4[size+1];
	sprintf(luaL_loadbufferxvar4, "/tmp/op1fx");
   lua_Integer lua_pushintegervar1;
	memset(&lua_pushintegervar1, 0, sizeof(lua_pushintegervar1));

   lua_State* luaL_newstateval1 = luaL_newstate();
	if(!luaL_newstateval1){
		fprintf(stderr, "err");
		exit(0);	}
   int luaL_loadbufferxval1 = luaL_loadbufferx(luaL_newstateval1, fuzzData, size, fuzzData, luaL_loadbufferxvar4);
	if((int)luaL_loadbufferxval1 < 0){
		fprintf(stderr, "err");
		exit(0);	}
   lua_settop(luaL_newstateval1, LUA_GCINC);
   lua_pushinteger(luaL_newstateval1, lua_pushintegervar1);
   char* lua_tolstringval1 = lua_tolstring(luaL_newstateval1, -1, NULL);
	if(!lua_tolstringval1){
		fprintf(stderr, "err");
		exit(0);	}
   return 0;
}
