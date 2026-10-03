#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
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
  char* null316 = NULL;
  TF_String const319 = "qkI85WfRMq2F";
  TF_String const321 = "%v4g]htjRO0tBy2";
  int var363 = luaL_loadbufferx(var50, null316, const305, const319, const321);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var50);
  traffic_assert(true);
}