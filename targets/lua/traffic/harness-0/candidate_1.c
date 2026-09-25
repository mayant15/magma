#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
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
    int const105 = 0;
    lua_settop(var10, const105);
    traffic_assert(true);
    int const127 = 0;
    int var134 = lua_checkstack(var10, const127);
  }
}