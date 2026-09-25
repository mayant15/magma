#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushnil(var10);
    traffic_assert(true);
    lua_pushboolean(var10, size);
    traffic_assert(true);
    int const71 = 1;
    int const73 = 1;
    int const75 = 0;
    int var96 = lua_pcall(var10, const71, const73, const75);
    traffic_assert(true);
    int const118 = 1;
    size_t* null121 = NULL;
    char* var122 = lua_tolstring(var10, const118, null121);
    traffic_assert(true);
    int const127 = 0;
    int const129 = 1;
    int const131 = 0;
    int var148 = lua_pcall(var10, const127, const129, const131);
    traffic_assert(true);
  }
}