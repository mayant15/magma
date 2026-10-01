#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_4(char* data, int size) {
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
  char* var316 = lua_tolstring(var50, const258, out260);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_pushboolean(var50, size);
  traffic_assert(true);
  traffic_assert(true);
  lua_settop(var50, var101);
  traffic_assert(true);
  traffic_assert(true);
  size_t out472_slot; size_t* out472 = &out472_slot;
  char* var474 = lua_tolstring(var50, const258, out472);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int const496 = -1;
  int const498 = -1;
  void* null501 = NULL;
  int var528 = lua_pcallk(var50, const258, const191, const496, const498, null501);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  char* null536 = NULL;
  TF_String const539 = "fDo9REQnXwU]jW";
  TF_String const541 = "[OUJQhJ38zts";
  int var583 = luaL_loadbufferx(var50, null536, const191, const539, const541);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var50);
  traffic_assert(true);
}