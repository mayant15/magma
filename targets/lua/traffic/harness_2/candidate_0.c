#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    TF_String const16 = "93Uy$UV)e340";
    TF_String const18 = "t";
    int var38 = luaL_loadbufferx(var10, data, size, const16, const18);
    traffic_assert(true);
    int const55 = 0;
    lua_settop(var10, const55);
    traffic_assert(true);
    int const78 = 0;
    int var85 = lua_checkstack(var10, const78);
  }
}