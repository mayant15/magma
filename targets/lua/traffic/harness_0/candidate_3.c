#include <traffic.h>

#include <lauxlib.h>

#include <lua.h>

int fuzz_3(char* data, int size) {
  lua_State* var10 = luaL_newstate();
  if (!((var10 == NULL))) {
    traffic_assert(true);
    int const27 = 0;
    int var38 = lua_checkstack(var10, const27);
    if (!((var38 == 0))) {
      traffic_assert(true);
      lua_close(var10);
    } else if ((var38 == 0)) {
      traffic_assert(true);
    }
  }
}