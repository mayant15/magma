#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_5(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    int var38 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
    lua_pushinteger(var10, size);
    traffic_assert(true);
    int const72 = 1;
    int const74 = 0;
    int const76 = 0;
    void* null79 = NULL;
    int var99 = lua_pcallk(var10, var38, const72, const74, const76, null79);
    traffic_assert(true);
    int const125 = 1;
    size_t* null128 = NULL;
    char* var129 = lua_tolstring(var10, const125, null128);
    traffic_assert(true);
  }
}