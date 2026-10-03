#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int var101 = lua_gettop(var50);
  traffic_assert(true);
  lua_pushboolean(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  int var205 = lua_checkstack(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  char* null211 = NULL;
  int const212 = -1;
  TF_String const214 = "u!lF4nhf4vS";
  TF_String const216 = "v&9KwerQ1gm0Yt";
  int var258 = luaL_loadbufferx(var50, null211, const212, const214, const216);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null313 = NULL;
  char* var314 = lua_tolstring(var50, var205, null313);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var50);
  traffic_assert(true);
}