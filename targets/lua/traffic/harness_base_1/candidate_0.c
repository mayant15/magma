#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int const93 = -1;
  lua_pushboolean(var50, const93);
  traffic_assert(true);
  traffic_assert(true);
  size_t out151_slot; size_t* out151 = &out151_slot;
  char* var153 = lua_tolstring(var50, const93, out151);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const185 = 1;
  lua_settop(var50, const185);
  traffic_assert(true);
  traffic_assert(true);
  int const223 = -1;
  int const225 = -1;
  void* null232 = NULL;
  int var259 = lua_pcallk(var50, const223, const225, const93, size, null232);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null313 = NULL;
  char* var314 = lua_tolstring(var50, const225, null313);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const324 = "oWjTynzFT1$Fl)Ultku";
  TF_String const326 = "xzKiVlPU";
  int var368 = luaL_loadbufferx(var50, data, var259, const324, const326);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushinteger(var50, var259);
  traffic_assert(true);
  traffic_assert(true);
  int const468 = 0;
  lua_pushboolean(var50, const468);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var50);
  traffic_assert(true);
}