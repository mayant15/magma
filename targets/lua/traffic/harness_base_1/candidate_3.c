#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  size_t* null92 = NULL;
  char* var93 = lua_tolstring(var46, size, null92);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var143 = lua_checkstack(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  int var192 = lua_checkstack(var46, size);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, var192);
  traffic_assert(true);
  traffic_assert(true);
  size_t* null288 = NULL;
  char* var289 = lua_tolstring(var46, var192, null288);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var339 = lua_pcall(var46, var143, size, var192);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const386 = 1;
  size_t out388_slot; size_t* out388 = &out388_slot;
  char* var390 = lua_tolstring(var46, const386, out388);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const436 = 0;
  char* var440 = lua_tolstring(var46, const436, null92);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, var339);
  traffic_assert(true);
  traffic_assert(true);
  int const510 = 0;
  int var538 = lua_pcall(var46, var143, var192, const510);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}