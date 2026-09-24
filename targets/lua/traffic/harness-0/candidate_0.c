#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    lua_pushnil(var10);
    traffic_assert(true);
    TF_String const42 = "!9$eG";
    TF_String const44 = "bt";
    int var72 = luaL_loadbufferx(var10, data, size, const42, const44);
    traffic_assert(true);
    lua_close(var10);
  }
}