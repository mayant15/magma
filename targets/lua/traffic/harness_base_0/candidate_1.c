#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
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
  lua_close(var50);
  traffic_assert(true);
}