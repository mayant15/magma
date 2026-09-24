#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushnil(var10);
    traffic_assert(true);
    TF_String const42 = "!9$eG";
    TF_String const44 = "bt";
    int var72 = luaL_loadbufferx(var10, data, size, const42, const44);
    traffic_assert(true);
    int var99 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
    int const116 = 0;
    int var126 = lua_checkstack(var10, const116);
    traffic_assert(true);
    int const132 = 1;
    int const136 = 0;
    if ((var126 == 1)) {
      int var153 = lua_pcall(var10, const132, var126, const136);
      traffic_assert(true);
    } else {
    }
  }
}