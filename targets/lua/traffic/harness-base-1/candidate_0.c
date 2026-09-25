#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_0(char* data, int size) {
  lua_State* var46 = luaL_newstate();
  int const81 = 1;
  lua_pushinteger(var46, const81);
  traffic_assert(true);
  traffic_assert(true);
  int const99 = 0;
  TF_String const101 = "a4IVa9VQZ9qB@t";
  TF_String const103 = "&)pqbMuy#Uf9xDk@7#v";
  int var141 = luaL_loadbufferx(var46, data, const99, const101, const103);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  int var193 = luaL_loadbufferx(var46, data, size, const103, const101);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  traffic_assert(true);
  lua_close(var46);
  traffic_assert(true);
}