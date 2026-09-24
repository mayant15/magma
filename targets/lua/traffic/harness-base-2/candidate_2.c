#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  lua_pushinteger(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushboolean(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushnil(var46);
  traffic_assert(true);
  int var236 = lua_checkstack(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  int const253 = 1;
  int const255 = 0;
  int const257 = 1;
  int var285 = lua_pcall(var46, const253, const255, const257);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null335 = NULL;
  char* var336 = lua_tolstring(var46, const253, null335);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t out384_slot; size_t* out384 = &out384_slot;
  char* var386 = lua_tolstring(var46, const257, out384);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* var436 = lua_tolstring(var46, var285, out384);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}