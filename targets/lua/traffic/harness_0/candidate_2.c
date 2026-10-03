#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_2(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    TF_String const16 = "24#pNeszKRq6sjXjD";
    TF_String const18 = "t";
    int var38 = luaL_loadbufferx(var10, data, size, const16, const18);
    traffic_assert(true);
    int const43 = 0;
    int const45 = 1;
    int const49 = 0;
    void* null52 = NULL;
    if ((var38 == 0)) {
      int var68 = lua_pcallk(var10, const43, const45, var38, const49, null52);
      traffic_assert(true);
      lua_close(var10);
    } else {
    }
  }
}