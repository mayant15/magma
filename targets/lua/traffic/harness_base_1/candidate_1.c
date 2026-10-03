#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int var101 = lua_gettop(var50);
  traffic_assert(true);
  lua_pushboolean(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  int const169 = -1;
  int const173 = -1;
  void* null178 = NULL;
  int var205 = lua_pcallk(var50, const169, size, const173, var101, null178);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const216 = "W8Ai4";
  TF_String const218 = "@qrKusR";
  int var260 = luaL_loadbufferx(var50, data, const173, const216, const218);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}