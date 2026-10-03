#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_4(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushboolean(var10, size);
    traffic_assert(true);
    int const61 = 1;
    lua_pushinteger(var10, const61);
    traffic_assert(true);
    int const97 = 0;
    lua_pushboolean(var10, const97);
    traffic_assert(true);
    int const108 = 2;
    int const110 = 1;
    int const112 = 0;
    int const114 = 0;
    void* null117 = NULL;
    int var137 = lua_pcallk(var10, const108, const110, const112, const114, null117);
    traffic_assert(true);
    int const163 = 1;
    size_t* null166 = NULL;
    char* var167 = lua_tolstring(var10, const163, null166);
    traffic_assert(true);
  }
}