#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushboolean(var10, size);
    traffic_assert(true);
    int const67 = 1;
    size_t* null70 = NULL;
    char* var71 = lua_tolstring(var10, const67, null70);
    traffic_assert(true);
    int const88 = 0;
    lua_settop(var10, const88);
    traffic_assert(true);
    int const114 = 0;
    lua_settop(var10, const114);
    traffic_assert(true);
    int var143 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
  }
}