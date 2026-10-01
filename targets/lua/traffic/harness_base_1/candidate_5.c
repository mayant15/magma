#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_5(char* data, int size) {
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
  int const237 = -1;
  lua_settop(var50, const237);
  traffic_assert(true);
  traffic_assert(true);
  int const289 = 0;
  lua_settop(var50, const289);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var50, const185);
  traffic_assert(true);
  traffic_assert(true);
  int var415 = lua_checkstack(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  size_t out466_slot; size_t* out466 = &out466_slot;
  char* var468 = lua_tolstring(var50, const185, out466);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const488 = -1;
  int const492 = 1;
  void* null495 = NULL;
  int var522 = lua_pcallk(var50, var415, const488, const289, const492, null495);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}