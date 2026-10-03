#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
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
  int const224 = 1;
  int const226 = 0;
  int const228 = 1;
  int const230 = -1;
  void* null233 = NULL;
  int var260 = lua_pcallk(var50, const224, const226, const228, const230, null233);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var50, var260);
  traffic_assert(true);
  traffic_assert(true);
}