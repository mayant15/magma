#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_1(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    int const24 = 0;
    lua_settop(var10, const24);
    traffic_assert(true);
    TF_String const43 = "UvYmcZt)!wPxYjpje";
    TF_String const45 = "t";
    int var61 = luaL_loadbufferx(var10, data, size, const43, const45);
    traffic_assert(true);
    int var87 = lua_gettop(var10);
    traffic_assert(true);
    traffic_assert(true);
    size_t* null112 = NULL;
    char* var113 = lua_tolstring(var10, var87, null112);
    traffic_assert(true);
    int const126 = 0;
    lua_settop(var10, const126);
    traffic_assert(true);
    lua_close(var10);
  }
}