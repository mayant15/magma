#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_4(char* data, int size) {
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
  int const414 = 1;
  char* var418 = lua_tolstring(var50, const414, out307);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}