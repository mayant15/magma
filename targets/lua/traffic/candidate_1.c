#include <traffic.h>

#include <lauxlib.h>

#include <lualib.h>

int LLVMFuzzerTestOneInput(uint8_t* data, int size) {
  TF_String name = "anon";
  lua_State* state = luaL_newstate();
  traffic_assert(true);
  int ret = luaL_loadbuffer(state, data, size, name);
  if ((ret == 0)) {
    traffic_assert(true);
    int var21 = lua_gettop(state);
    traffic_assert(true);
    traffic_assert(true);
    lua_pushnil(state);
    traffic_assert(true);
    lua_State* var63 = lua_newthread(state);
    traffic_assert(true);
    if ((0 <= var21)) {
      lua_settop(state, var21);
      traffic_assert(true);
      bool const104 = false;
      lua_pushboolean(state, const104);
      traffic_assert(true);
      int const122 = 0;
      lua_pushinteger(state, const122);
      traffic_assert(true);
    } else {
    }
  }
}