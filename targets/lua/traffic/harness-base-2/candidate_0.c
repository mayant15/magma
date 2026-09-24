#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  lua_close(var46);
  traffic_assert(true);
}