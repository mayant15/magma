#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
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
  int const240 = 0;
  int var258 = lua_checkstack(var50, const240);
  traffic_assert(true);
  traffic_assert(true);
  int const275 = -1;
  int const277 = 0;
  int const279 = -1;
  void* null284 = NULL;
  int var311 = lua_pcallk(var50, const275, const277, const279, var258, null284);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const362 = 0;
  size_t out364_slot; size_t* out364 = &out364_slot;
  char* var366 = lua_tolstring(var50, const362, out364);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const384 = -1;
  int const386 = 1;
  void* null393 = NULL;
  int var420 = lua_pcallk(var50, const384, const386, const362, var311, null393);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null474 = NULL;
  char* var475 = lua_tolstring(var50, var155, null474);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}