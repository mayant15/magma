#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int const89 = 1;
  lua_pushinteger(var50, const89);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushnil(var50);
  traffic_assert(true);
  TF_String const160 = "e3Xe9oxy";
  TF_String const162 = "y13gzwt";
  int var204 = luaL_loadbufferx(var50, data, const89, const160, const162);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* null213 = NULL;
  TF_String const216 = "igg[@%i9$mAnKM[obfOR";
  TF_String const218 = "RmNrN4rTt(v";
  int var260 = luaL_loadbufferx(var50, null213, var204, const216, const218);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t out314_slot; size_t* out314 = &out314_slot;
  char* var316 = lua_tolstring(var50, const89, out314);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char out322_slot; char* out322 = &out322_slot;
  TF_String const328 = "GtWbllOI7qgiUdEnNMPU";
  int var370 = luaL_loadbufferx(var50, out322, const89, const218, const328);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const408 = 1;
  int var426 = lua_checkstack(var50, const408);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var50);
  traffic_assert(true);
}