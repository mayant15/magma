#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  int const75 = 1;
  int var93 = lua_checkstack(var46, const75);
  traffic_assert(true);
  traffic_assert(true);
  int var142 = lua_gettop(var46);
  traffic_assert(true);
  char* null147 = NULL;
  TF_String const150 = "]#FgDhrF#1dFUKj4#k";
  TF_String const152 = "w0Sobc#2D0fEo#ID";
  int var190 = luaL_loadbufferx(var46, null147, const75, const150, const152);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var46);
  traffic_assert(true);
}