#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushnil(var10);
    traffic_assert(true);
    int const50 = 0;
    lua_settop(var10, const50);
    traffic_assert(true);
    int const80 = 0;
    lua_settop(var10, const80);
    traffic_assert(true);
    TF_String const95 = "JB@^0KCOVDj@";
    TF_String const97 = "t";
    int var113 = luaL_loadbufferx(var10, data, size, const95, const97);
    traffic_assert(true);
    lua_close(var10);
  }
}