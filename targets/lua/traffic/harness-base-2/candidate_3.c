#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  lua_pushinteger(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushboolean(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  int const171 = -1;
  int var189 = lua_checkstack(var46, const171);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const198 = "cSbOWp[J@z)SPA@";
  TF_String const200 = "@SN!9BVy2JX";
  int var238 = luaL_loadbufferx(var46, data, const171, const198, const200);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null289 = NULL;
  char* var290 = lua_tolstring(var46, const171, null289);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, var238);
  traffic_assert(true);
  traffic_assert(true);
  int const366 = 0;
  lua_settop(var46, const366);
  traffic_assert(true);
  traffic_assert(true);
  char* var436 = lua_tolstring(var46, var238, null289);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const478 = 0;
  lua_pushboolean(var46, const478);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, var238);
  traffic_assert(true);
  traffic_assert(true);
  int var582 = lua_pcall(var46, const478, var238, const171);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, const171);
  traffic_assert(true);
  traffic_assert(true);
  int var681 = lua_pcall(var46, var238, var582, const366);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const702 = -1;
  int var732 = lua_pcall(var46, const366, const702, var582);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const741 = -1;
  TF_String const743 = "(DHAHIg](6xl6R2";
  TF_String const745 = "7w5zftL%ddid";
  int var783 = luaL_loadbufferx(var46, var436, const741, const743, const745);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const803 = 1;
  int var835 = lua_pcall(var46, const803, const366, const171);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var46);
  traffic_assert(true);
}