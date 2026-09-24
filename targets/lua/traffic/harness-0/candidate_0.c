#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushinteger(var10, size);
    traffic_assert(true);
    int const53 = 0;
    int var67 = lua_checkstack(var10, const53);
  }
}