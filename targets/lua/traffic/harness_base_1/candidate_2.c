#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  size_t out99_slot; size_t* out99 = &out99_slot;
  char* var101 = lua_tolstring(var50, size, out99);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var155 = lua_gettop(var50);
  traffic_assert(true);
  lua_pushnil(var50);
  traffic_assert(true);
  char* null211 = NULL;
  int const212 = 0;
  TF_String const214 = "bRw9myRbfA%(r";
  TF_String const216 = "(7VDl9@CP)ieTVo";
  int var258 = luaL_loadbufferx(var50, null211, const212, const214, const216);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const272 = "y]Qt70nAI(vJH!l";
  int var314 = luaL_loadbufferx(var50, null211, size, const216, const272);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const336 = -1;
  int const340 = 1;
  void* null343 = NULL;
  int var370 = lua_pcallk(var50, const212, const336, size, const340, null343);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var425 = luaL_loadbufferx(var50, data, const212, const214, const216);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* null434 = NULL;
  int const435 = 1;
  TF_String const437 = "T$GR^09mc8";
  int var481 = luaL_loadbufferx(var50, null434, const435, const437, const272);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var50);
  traffic_assert(true);
}