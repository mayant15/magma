#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_4(char* data, int size) {
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
  size_t* null316 = NULL;
  char* var317 = lua_tolstring(var50, const83, null316);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* var371 = lua_tolstring(var50, var101, null316);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const403 = -1;
  lua_settop(var50, const403);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  int const521 = 0;
  lua_pushboolean(var50, const521);
  traffic_assert(true);
  traffic_assert(true);
  int const545 = -1;
  int const547 = 1;
  int const549 = -1;
  void* null554 = NULL;
  int var581 = lua_pcallk(var50, const545, const547, const549, const178, null554);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null635 = NULL;
  char* var636 = lua_tolstring(var50, const549, null635);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const686 = 0;
  size_t out688_slot; size_t* out688 = &out688_slot;
  char* var690 = lua_tolstring(var50, const686, out688);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}