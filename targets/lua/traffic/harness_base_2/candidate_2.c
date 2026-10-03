#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int const89 = 1;
  lua_pushinteger(var50, const89);
  traffic_assert(true);
  traffic_assert(true);
  int const135 = 0;
  int var153 = lua_checkstack(var50, const135);
  traffic_assert(true);
  traffic_assert(true);
  size_t out204_slot; size_t* out204 = &out204_slot;
  char* var206 = lua_tolstring(var50, size, out204);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var260 = lua_gettop(var50);
  traffic_assert(true);
  int const276 = -1;
  int const278 = 0;
  int const282 = 0;
  void* null285 = NULL;
  int var312 = lua_pcallk(var50, const276, const278, const135, const282, null285);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var50, const278);
  traffic_assert(true);
  traffic_assert(true);
}