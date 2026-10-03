#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_6(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int const89 = 1;
  lua_pushinteger(var50, const89);
  traffic_assert(true);
  traffic_assert(true);
  int const135 = 0;
  int var153 = lua_checkstack(var50, const135);
  traffic_assert(true);
  traffic_assert(true);
  int const202 = -1;
  size_t* null205 = NULL;
  char* var206 = lua_tolstring(var50, const202, null205);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* var260 = lua_tolstring(var50, var153, null205);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var50, const202);
  traffic_assert(true);
  traffic_assert(true);
  int const320 = 1;
  TF_String const322 = "pEOFZm33EUGMDF^mW";
  TF_String const324 = "6m8Zt";
  int var366 = luaL_loadbufferx(var50, var260, const320, const322, const324);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* null375 = NULL;
  int const376 = 0;
  int var422 = luaL_loadbufferx(var50, null375, const376, const322, const324);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const436 = "t!lKz7n5v8]$k83rS";
  int var478 = luaL_loadbufferx(var50, data, var366, const322, const436);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const500 = -1;
  int const504 = 0;
  void* null507 = NULL;
  int var534 = lua_pcallk(var50, const89, const500, const135, const504, null507);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var50);
  traffic_assert(true);
}