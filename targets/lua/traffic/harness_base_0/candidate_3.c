#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int const83 = -1;
  int var101 = lua_checkstack(var50, const83);
  traffic_assert(true);
  traffic_assert(true);
  char out106_slot; char* out106 = &out106_slot;
  TF_String const110 = "$w3Fyg%8zP%[iV%ro";
  TF_String const112 = "RK)r9gyHK8!2V)F";
  int var154 = luaL_loadbufferx(var50, out106, const83, const110, const112);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const178 = 1;
  void* null183 = NULL;
  int var210 = lua_pcallk(var50, var101, const83, const178, size, null183);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushboolean(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushnil(var50);
  traffic_assert(true);
  int const334 = 1;
  int const338 = -1;
  void* null341 = NULL;
  int var368 = lua_pcallk(var50, const178, const334, var101, const338, null341);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var423 = lua_gettop(var50);
  traffic_assert(true);
  size_t out473_slot; size_t* out473 = &out473_slot;
  char* var475 = lua_tolstring(var50, var368, out473);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}