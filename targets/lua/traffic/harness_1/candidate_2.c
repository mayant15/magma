#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushboolean(var10, size);
    traffic_assert(true);
    int const61 = 1;
    lua_pushinteger(var10, const61);
    traffic_assert(true);
    int const90 = 0;
    int var104 = lua_checkstack(var10, const90);
  }
}