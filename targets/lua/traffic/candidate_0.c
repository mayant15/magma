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
    int const101 = 0;
    lua_State* var431 = lua_tothread(state, const101);
    traffic_assert(true);
    traffic_assert(true);
    lua_State* null491 = NULL;
    int const492 = 0;
    char* var855 = lua_typename(null491, const492);
    traffic_assert(true);
    traffic_assert(true);
    lua_Debug* null1207 = NULL;
    int const1208 = 0;
    char* var1279 = lua_getlocal(state, null1207, const1208);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
  }
}