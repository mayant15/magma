#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushboolean(var10, size);
    traffic_assert(true);
    int var71 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
    lua_pushnil(var10);
    traffic_assert(true);
  }
}