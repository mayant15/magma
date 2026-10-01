#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushnil(var10);
    traffic_assert(true);
    int const54 = 0;
    lua_settop(var10, const54);
    traffic_assert(true);
    lua_close(var10);
  }
}