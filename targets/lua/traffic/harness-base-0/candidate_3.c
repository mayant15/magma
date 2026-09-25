#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  int const75 = 1;
  int var93 = lua_checkstack(var46, const75);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushboolean(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, const75);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null237 = NULL;
  char* var238 = lua_tolstring(var46, const75, null237);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var288 = lua_pcall(var46, var93, size, const75);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* var339 = lua_tolstring(var46, var93, null237);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const385 = 1;
  size_t out387_slot; size_t* out387 = &out387_slot;
  char* var389 = lua_tolstring(var46, const385, out387);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, const385);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, var288);
  traffic_assert(true);
  traffic_assert(true);
  int const505 = -1;
  int var535 = lua_pcall(var46, const385, const505, const75);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}