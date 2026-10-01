#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_4(char* data, int size) {
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
    int var113 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
    TF_String const119 = "@pnLsjSeb%jc";
    TF_String const121 = "t";
    int var137 = luaL_loadbufferx(var10, data, size, const119, const121);
    traffic_assert(true);
    int const144 = 1;
    if ((var137 == 0)) {
      int var163 = lua_pcall(var10, var113, const144, var137);
      traffic_assert(true);
      lua_close(var10);
    } else {
      int const170 = 1;
      int const172 = 0;
      int var189 = lua_pcall(var10, var113, const170, const172);
      traffic_assert(true);
    }
  }
}