#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  lua_pushnil(var46);
  traffic_assert(true);
  int const122 = -1;
  int var140 = lua_checkstack(var46, const122);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushinteger(var46, const122);
  traffic_assert(true);
  traffic_assert(true);
  char* null194 = NULL;
  TF_String const197 = "zhV%iUzeSoBgC5gc";
  TF_String const199 = "7GLdrASdZj)$1q%h2V";
  int var237 = luaL_loadbufferx(var46, null194, const122, const197, const199);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, var140);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var46);
  traffic_assert(true);
}