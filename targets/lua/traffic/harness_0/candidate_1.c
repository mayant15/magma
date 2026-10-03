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
  }
}