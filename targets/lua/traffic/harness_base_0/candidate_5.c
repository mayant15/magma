#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_5(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int var101 = lua_gettop(var50);
  traffic_assert(true);
  lua_pushboolean(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushnil(var50);
  traffic_assert(true);
  size_t out254_slot; size_t* out254 = &out254_slot;
  char* var256 = lua_tolstring(var50, size, out254);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const278 = 0;
  int const280 = 0;
  void* null283 = NULL;
  int var310 = lua_pcallk(var50, var101, size, const278, const280, null283);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null364 = NULL;
  char* var365 = lua_tolstring(var50, var310, null364);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  void* null392 = NULL;
  int var419 = lua_pcallk(var50, var310, size, var101, const278, null392);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var50, var310);
  traffic_assert(true);
  traffic_assert(true);
}