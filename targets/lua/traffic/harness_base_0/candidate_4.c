#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_4(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int var101 = lua_gettop(var50);
  traffic_assert(true);
  lua_pushboolean(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  int var205 = lua_checkstack(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  int const254 = -1;
  size_t out256_slot; size_t* out256 = &out256_slot;
  char* var258 = lua_tolstring(var50, const254, out256);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  TF_String const268 = "rU*6uv9!vgcr#Ox";
  TF_String const270 = "XUFbrWwVjiFo6t";
  int var312 = luaL_loadbufferx(var50, data, var205, const268, const270);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* var368 = lua_tolstring(var50, const254, out256);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}