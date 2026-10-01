#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushboolean(var10, size);
    traffic_assert(true);
    int const57 = 0;
    int var71 = lua_checkstack(var10, const57);
  }
}