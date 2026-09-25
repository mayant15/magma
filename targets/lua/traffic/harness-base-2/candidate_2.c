#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
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
  size_t out335_slot; size_t* out335 = &out335_slot;
  char* var337 = lua_tolstring(var46, var237, out335);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const355 = 1;
  int const359 = 0;
  int var387 = lua_pcall(var46, const355, const122, const359);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, var387);
  traffic_assert(true);
  traffic_assert(true);
  size_t out484_slot; size_t* out484 = &out484_slot;
  char* var486 = lua_tolstring(var46, const355, out484);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const532 = 0;
  size_t* null535 = NULL;
  char* var536 = lua_tolstring(var46, const532, null535);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var586 = lua_gettop(var46);
  traffic_assert(true);
  int const626 = 0;
  lua_pushboolean(var46, const626);
  traffic_assert(true);
  traffic_assert(true);
  int var682 = lua_checkstack(var46, size);
  traffic_assert(true);
  traffic_assert(true);
}