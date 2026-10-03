#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_5(char* data, int size) {
  lua_State* var50 = luaL_newstate();
  int const89 = 1;
  lua_pushinteger(var50, const89);
  traffic_assert(true);
  traffic_assert(true);
  int const135 = 0;
  int var153 = lua_checkstack(var50, const135);
  traffic_assert(true);
  traffic_assert(true);
  size_t out204_slot; size_t* out204 = &out204_slot;
  char* var206 = lua_tolstring(var50, size, out204);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const224 = 1;
  int const226 = 0;
  int const228 = 1;
  int const230 = -1;
  void* null233 = NULL;
  int var260 = lua_pcallk(var50, const224, const226, const228, const230, null233);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const307 = 0;
  lua_pushboolean(var50, const307);
  traffic_assert(true);
  traffic_assert(true);
  char out319_slot; char* out319 = &out319_slot;
  TF_String const323 = "m)8#*qju8!";
  TF_String const325 = "WV15k4GcV^Nm$TA)21";
  int var367 = luaL_loadbufferx(var50, out319, var260, const323, const325);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const387 = -1;
  int const389 = -1;
  void* null396 = NULL;
  int var423 = lua_pcallk(var50, const387, const389, var367, const89, null396);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const448 = 1;
  void* null451 = NULL;
  int var478 = lua_pcallk(var50, var153, const135, const389, const448, null451);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
}