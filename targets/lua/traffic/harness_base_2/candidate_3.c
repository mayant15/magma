#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  TF_String const57 = "mDBj@fra";
  TF_String const59 = "ReLA)O1!5S*";
  int var101 = luaL_loadbufferx(var50, data, size, const57, const59);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushinteger(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  int const191 = -1;
  int var209 = lua_checkstack(var50, const191);
  traffic_assert(true);
  traffic_assert(true);
  int const258 = -1;
  size_t out260_slot; size_t* out260 = &out260_slot;
  char* var262 = lua_tolstring(var50, const258, out260);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* null269 = NULL;
  int const270 = 0;
  int var316 = luaL_loadbufferx(var50, null269, const270, const59, const57);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var372 = lua_gettop(var50);
  traffic_assert(true);
  size_t* null423 = NULL;
  char* var424 = lua_tolstring(var50, const270, null423);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const444 = 0;
  void* null451 = NULL;
  int var478 = lua_pcallk(var50, var101, const444, var316, size, null451);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  void* null506 = NULL;
  int var533 = lua_pcallk(var50, const191, const258, const270, const444, null506);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const584 = 1;
  size_t* null587 = NULL;
  char* var588 = lua_tolstring(var50, const584, null587);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}