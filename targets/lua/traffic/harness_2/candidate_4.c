#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_4(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    int var38 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
    lua_pushnil(var10);
    traffic_assert(true);
    int const95 = 1;
    size_t* null98 = NULL;
    char* var99 = lua_tolstring(var10, const95, null98);
    traffic_assert(true);
    if (!((var99 == NULL))) {
    } else if ((var99 == NULL)) {
      int const126 = 0;
      lua_pushboolean(var10, const126);
      traffic_assert(true);
    }
  }
}