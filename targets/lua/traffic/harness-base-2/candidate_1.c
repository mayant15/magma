#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
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
  int var388 = lua_pcall(var46, const171, var189, var238);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var439 = lua_gettop(var46);
  traffic_assert(true);
  size_t out485_slot; size_t* out485 = &out485_slot;
  char* var487 = lua_tolstring(var46, var238, out485);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const495 = 0;
  TF_String const497 = "2FiXi[&A7sSh";
  int var537 = luaL_loadbufferx(var46, var487, const495, const497, const200);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}