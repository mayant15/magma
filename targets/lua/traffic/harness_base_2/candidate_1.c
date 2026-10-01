#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  TF_String const57 = "mDBj@fra";
  TF_String const59 = "ReLA)O1!5S*";
  int var101 = luaL_loadbufferx(var50, data, size, const57, const59);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushnil(var50);
  traffic_assert(true);
  lua_settop(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  int var260 = lua_checkstack(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  int const277 = -1;
  int const283 = 1;
  void* null286 = NULL;
  int var313 = lua_pcallk(var50, const277, var101, size, const283, null286);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}