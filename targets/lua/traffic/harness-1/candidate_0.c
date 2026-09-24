#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    int const24 = 0;
    lua_settop(var10, const24);
    traffic_assert(true);
    int const54 = 0;
    int var61 = lua_checkstack(var10, const54);
  }
}