#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
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
    int const89 = 1;
    size_t* null92 = NULL;
    char* var93 = lua_tolstring(var10, const89, null92);
    traffic_assert(true);
    int const98 = 0;
    int const100 = 1;
    int const102 = 0;
    int var119 = lua_pcall(var10, const98, const100, const102);
    traffic_assert(true);
    int const124 = 0;
    int const126 = 1;
    int const128 = 0;
    int var145 = lua_pcall(var10, const124, const126, const128);
    traffic_assert(true);
  }
}