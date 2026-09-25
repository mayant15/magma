#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_4(char* data, int size) {
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
  int var241 = lua_checkstack(var46, var192);
  traffic_assert(true);
  traffic_assert(true);
  int const286 = -1;
  char* var290 = lua_tolstring(var46, const286, null92);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const308 = 0;
  int const310 = 1;
  int var340 = lua_pcall(var46, const308, const310, const286);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var46, const286);
  traffic_assert(true);
  traffic_assert(true);
  int const435 = 0;
  size_t out437_slot; size_t* out437 = &out437_slot;
  char* var439 = lua_tolstring(var46, const435, out437);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const457 = -1;
  int var489 = lua_pcall(var46, const457, const286, const310);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char out496_slot; char* out496 = &out496_slot;
  int const498 = 1;
  TF_String const500 = "8D^%IIZ&(V&][8yN";
  TF_String const502 = "JJdXx#Ath(hp";
  int var540 = luaL_loadbufferx(var46, out496, const498, const500, const502);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  size_t out590_slot; size_t* out590 = &out590_slot;
  char* var592 = lua_tolstring(var46, var340, out590);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const624 = -1;
  int var642 = lua_checkstack(var46, const624);
  traffic_assert(true);
  traffic_assert(true);
  int const679 = 1;
  lua_pushinteger(var46, const679);
  traffic_assert(true);
  traffic_assert(true);
  char* var739 = lua_tolstring(var46, var192, null92);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushboolean(var46, const435);
  traffic_assert(true);
  traffic_assert(true);
}