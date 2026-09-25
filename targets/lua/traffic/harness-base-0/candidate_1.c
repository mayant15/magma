#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  int const75 = 1;
  int var93 = lua_checkstack(var46, const75);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushboolean(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushinteger(var46, var93);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushnil(var46);
  traffic_assert(true);
  int var285 = lua_checkstack(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  int const302 = 0;
  int const304 = 1;
  int var334 = lua_pcall(var46, const302, const304, size);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const355 = 0;
  int const357 = 0;
  int var385 = lua_pcall(var46, var285, const355, const357);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const414 = -1;
  lua_settop(var46, const414);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, var285);
  traffic_assert(true);
  traffic_assert(true);
  int const528 = 0;
  size_t out530_slot; size_t* out530 = &out530_slot;
  char* var532 = lua_tolstring(var46, const528, out530);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* null539 = NULL;
  int const540 = 1;
  TF_String const542 = "boq6bpYd";
  TF_String const544 = "AXu2(QhwAN9TCtykFaIc";
  int var582 = luaL_loadbufferx(var46, null539, const540, const542, const544);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var46);
  traffic_assert(true);
}