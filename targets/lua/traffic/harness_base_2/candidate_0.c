#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  TF_String const57 = "mDBj@fra";
  TF_String const59 = "ReLA)O1!5S*";
  int var101 = luaL_loadbufferx(var50, data, size, const57, const59);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushinteger(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  int const191 = -1;
  int var209 = lua_checkstack(var50, const191);
  traffic_assert(true);
  traffic_assert(true);
  int const226 = -1;
  int const228 = -1;
  void* null235 = NULL;
  int var262 = lua_pcallk(var50, const226, const228, var101, size, null235);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const309 = 0;
  lua_pushboolean(var50, const309);
  traffic_assert(true);
  traffic_assert(true);
}