#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    int var38 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
    lua_pushinteger(var10, size);
    traffic_assert(true);
    int const85 = 0;
    int var99 = lua_checkstack(var10, const85);
    if (!((var99 == 0))) {
      traffic_assert(true);
      int const117 = 0;
      lua_settop(var10, const117);
      traffic_assert(true);
    } else if ((var99 == 0)) {
      traffic_assert(true);
    }
  }
}