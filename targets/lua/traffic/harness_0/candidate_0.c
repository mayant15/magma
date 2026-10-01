#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushinteger(var10, size);
    traffic_assert(true);
    lua_pushnil(var10);
    traffic_assert(true);
    int const79 = 0;
    lua_settop(var10, const79);
    traffic_assert(true);
    int var115 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
  }
}