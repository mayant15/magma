#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
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
    size_t* null125 = NULL;
    char* var126 = lua_tolstring(var10, var99, null125);
    traffic_assert(true);
    int const140 = 0;
    lua_settop(var10, const140);
    traffic_assert(true);
    if (((0 <= var72) && (var72 < 256))) {
      lua_settop(var10, var72);
      traffic_assert(true);
    } else {
    }
  }
}