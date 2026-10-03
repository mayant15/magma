#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    int var38 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
    TF_String const44 = "Ib9Zg^TOXR&Kbl84d&p";
    TF_String const46 = "t";
    int var66 = luaL_loadbufferx(var10, data, size, const44, const46);
    traffic_assert(true);
    lua_close(var10);
    lua_State* var106 = luaL_newstate();
  }
}