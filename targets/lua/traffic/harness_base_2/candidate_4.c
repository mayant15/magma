#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_4(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int var101 = lua_checkstack(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null153 = NULL;
  char* var154 = lua_tolstring(var50, var101, null153);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}