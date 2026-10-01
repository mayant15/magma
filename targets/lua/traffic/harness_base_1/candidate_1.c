#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  lua_pushnil(var46);
  traffic_assert(true);
  int const132 = -1;
  lua_pushboolean(var46, const132);
  traffic_assert(true);
  traffic_assert(true);
  int const156 = -1;
  int const158 = 0;
  int const160 = 1;
  int var188 = lua_pcall(var46, const156, const158, const160);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}