#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_6(char* data, int size) {
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
  lua_settop(var50, var205);
  traffic_assert(true);
  traffic_assert(true);
  size_t out311_slot; size_t* out311 = &out311_slot;
  char* var313 = lua_tolstring(var50, var205, out311);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var367 = lua_checkstack(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null419 = NULL;
  char* var420 = lua_tolstring(var50, size, null419);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const444 = -1;
  void* null447 = NULL;
  int var474 = lua_pcallk(var50, var205, var101, var367, const444, null447);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}