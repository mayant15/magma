#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_8(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int var101 = lua_gettop(var50);
  traffic_assert(true);
  lua_pushinteger(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushnil(var50);
  traffic_assert(true);
  int var256 = lua_checkstack(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  int const305 = -1;
  size_t out307_slot; size_t* out307 = &out307_slot;
  char* var309 = lua_tolstring(var50, const305, out307);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const327 = -1;
  int const333 = 0;
  void* null336 = NULL;
  int var363 = lua_pcallk(var50, const327, size, var101, const333, null336);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t out416_slot; size_t* out416 = &out416_slot;
  char* var418 = lua_tolstring(var50, const305, out416);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const440 = -1;
  int const442 = 0;
  void* null445 = NULL;
  int var472 = lua_pcallk(var50, var363, const327, const440, const442, null445);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const535 = "mjt@f)lqc5j$4j9lfs&9";
  TF_String const537 = "H#!hZt[";
  int var579 = luaL_loadbufferx(var50, var418, var363, const535, const537);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const599 = -1;
  int const601 = 0;
  int const603 = 0;
  void* null608 = NULL;
  int var635 = lua_pcallk(var50, const599, const601, const603, const327, null608);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}