#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushnil(var10);
    traffic_assert(true);
    lua_pushboolean(var10, size);
    traffic_assert(true);
    int const92 = 2;
    size_t* null95 = NULL;
    char* var96 = lua_tolstring(var10, const92, null95);
    traffic_assert(true);
    int const119 = 0;
    lua_pushboolean(var10, const119);
    traffic_assert(true);
    int const145 = 0;
    lua_pushinteger(var10, const145);
    traffic_assert(true);
    int const180 = 4;
    size_t* null183 = NULL;
    char* var184 = lua_tolstring(var10, const180, null183);
    traffic_assert(true);
  }
}