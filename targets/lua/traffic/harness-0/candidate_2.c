#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushinteger(var10, size);
    traffic_assert(true);
    int const50 = 0;
    lua_settop(var10, const50);
    traffic_assert(true);
    int const76 = 0;
    lua_settop(var10, const76);
    traffic_assert(true);
    int var105 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
  }
}