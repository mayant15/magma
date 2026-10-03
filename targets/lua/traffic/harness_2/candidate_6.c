#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_6(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    int var38 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
    lua_pushinteger(var10, size);
    traffic_assert(true);
    int const95 = 1;
    size_t* null98 = NULL;
    char* var99 = lua_tolstring(var10, const95, null98);
    traffic_assert(true);
    int const106 = 1;
    int const108 = 0;
    int const110 = 0;
    void* null113 = NULL;
    int var133 = lua_pcallk(var10, var38, const106, const108, const110, null113);
    traffic_assert(true);
  }
}