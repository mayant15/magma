#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_7(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int var101 = lua_gettop(var50);
  traffic_assert(true);
  lua_pushinteger(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null256 = NULL;
  char* var257 = lua_tolstring(var50, var101, null256);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const267 = "foJcKzhFD41G";
  TF_String const269 = "cfLv%qc[tr6kG";
  int var311 = luaL_loadbufferx(var50, var257, var101, const267, const269);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* null320 = NULL;
  int const321 = -1;
  int var367 = luaL_loadbufferx(var50, null320, const321, const267, const269);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const391 = -1;
  void* null396 = NULL;
  int var423 = lua_pcallk(var50, var311, const321, const391, var367, null396);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}