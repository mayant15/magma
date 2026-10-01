#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  int const75 = 1;
  int var93 = lua_checkstack(var46, const75);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushboolean(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushinteger(var46, var93);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const198 = "!8%eKB";
  TF_String const200 = "hCyy8IRoX&o@[(Eh";
  int var238 = luaL_loadbufferx(var46, data, var93, const198, const200);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const248 = 0;
  TF_String const250 = "Ie59^A$33W9r*GX";
  int var290 = luaL_loadbufferx(var46, data, const248, const250, const200);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const314 = 1;
  int var342 = lua_pcall(var46, const75, var238, const314);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushboolean(var46, const248);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null440 = NULL;
  char* var441 = lua_tolstring(var46, var238, null440);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const463 = -1;
  int var491 = lua_pcall(var46, const75, var290, const463);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}