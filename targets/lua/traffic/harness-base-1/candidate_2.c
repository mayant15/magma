#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  int var93 = lua_gettop(var46);
  traffic_assert(true);
  lua_pushboolean(var46, var93);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, var93);
  traffic_assert(true);
  traffic_assert(true);
}