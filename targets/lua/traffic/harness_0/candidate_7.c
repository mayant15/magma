#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_7(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushinteger(var10, size);
    traffic_assert(true);
    int const42 = 0;
    int const44 = 1;
    int const46 = 0;
    int const48 = 0;
    void* null51 = NULL;
    int var71 = lua_pcallk(var10, const42, const44, const46, const48, null51);
    traffic_assert(true);
    int const97 = 1;
    size_t* null100 = NULL;
    char* var101 = lua_tolstring(var10, const97, null100);
    traffic_assert(true);
  }
}