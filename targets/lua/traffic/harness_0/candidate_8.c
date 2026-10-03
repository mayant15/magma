#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_8(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushinteger(var10, size);
    traffic_assert(true);
    int const64 = 0;
    lua_pushboolean(var10, const64);
    traffic_assert(true);
    int const97 = 1;
    lua_pushboolean(var10, const97);
    traffic_assert(true);
  }
}