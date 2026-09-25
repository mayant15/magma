#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushinteger(var10, size);
    traffic_assert(true);
    int const42 = 0;
    int const44 = 1;
    int const46 = 0;
    int var67 = lua_pcall(var10, const42, const44, const46);
    traffic_assert(true);
    lua_close(var10);
  }
}