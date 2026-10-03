#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  lua_pushboolean(var50, size);
  traffic_assert(true);
  traffic_assert(true);
}