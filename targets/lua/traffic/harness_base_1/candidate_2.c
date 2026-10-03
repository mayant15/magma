#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
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
  lua_close(var50);
  traffic_assert(true);
}