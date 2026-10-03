#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int var101 = lua_gettop(var50);
  traffic_assert(true);
  lua_pushinteger(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  char* null158 = NULL;
  TF_String const161 = "sDceq*3PW)uITW";
  TF_String const163 = "9&dlPw)#(l";
  int var205 = luaL_loadbufferx(var50, null158, var101, const161, const163);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushboolean(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  size_t out311_slot; size_t* out311 = &out311_slot;
  char* var313 = lua_tolstring(var50, size, out311);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}