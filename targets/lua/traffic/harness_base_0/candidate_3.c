#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int var101 = lua_gettop(var50);
  traffic_assert(true);
  lua_pushboolean(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  int var205 = lua_checkstack(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  int const250 = 0;
  lua_pushboolean(var50, const250);
  traffic_assert(true);
  traffic_assert(true);
  char out262_slot; char* out262 = &out262_slot;
  TF_String const266 = "l1hy6)B";
  TF_String const268 = "V!PHucn0RK8Zq";
  int var310 = luaL_loadbufferx(var50, out262, var205, const266, const268);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const332 = 1;
  void* null339 = NULL;
  int var366 = lua_pcallk(var50, var205, const332, var101, size, null339);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const389 = -1;
  int const391 = 1;
  void* null394 = NULL;
  int var421 = lua_pcallk(var50, var205, const332, const389, const391, null394);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t out474_slot; size_t* out474 = &out474_slot;
  char* var476 = lua_tolstring(var50, const332, out474);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const496 = 1;
  int const500 = 1;
  void* null503 = NULL;
  int var530 = lua_pcallk(var50, const250, const496, var205, const500, null503);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}