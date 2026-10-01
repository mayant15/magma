#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
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
  lua_pushboolean(var46, const122);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, const122);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const393 = "RKEtd#xn*wnoNr*$c";
  TF_String const395 = "gsPc!";
  int var433 = luaL_loadbufferx(var46, data, var140, const393, const395);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const457 = -1;
  int var485 = lua_pcall(var46, const122, var140, const457);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null535 = NULL;
  char* var536 = lua_tolstring(var46, const122, null535);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const582 = -1;
  size_t out584_slot; size_t* out584 = &out584_slot;
  char* var586 = lua_tolstring(var46, const582, out584);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* null593 = NULL;
  int var636 = luaL_loadbufferx(var46, null593, var433, const197, const393);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var688 = lua_pcall(var46, var140, const457, const122);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var739 = lua_pcall(var46, const582, var485, var140);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char out746_slot; char* out746 = &out746_slot;
  TF_String const752 = "ttAzwympois@rx@q27z";
  int var790 = luaL_loadbufferx(var46, out746, var140, const197, const752);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var46);
  traffic_assert(true);
}