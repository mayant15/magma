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
    int var431 = luaopen_utf8(state);
    traffic_assert(true);
    int const801 = 0;
    char* var854 = lua_setupvalue(state, var431, const801);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    char out1068_slot; char* out1068 = &out1068_slot;
    lua_setglobal(state, out1068);
    traffic_assert(true);
    traffic_assert(true);
    int const1655 = 0;
    void* var1702 = lua_upvalueid(state, var431, const1655);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    int var2127 = lua_gethookcount(state);
    traffic_assert(true);
    luaL_openlibs(state);
    traffic_assert(true);
    luaL_openlibs(state);
    traffic_assert(true);
    char* null3105 = NULL;
    char* var3394 = lua_pushstring(state, null3105);
    traffic_assert(true);
    traffic_assert(true);
    int var3818 = lua_getmetatable(state, var2127);
    traffic_assert(true);
    traffic_assert(true);
    int const3994 = 0;
    int var4242 = lua_rawget(state, const3994);
    traffic_assert(true);
    traffic_assert(true);
    int const4489 = 0;
    int var4666 = lua_setmetatable(state, const4489);
    traffic_assert(true);
    traffic_assert(true);
    lua_closeslot(state, var431);
    traffic_assert(true);
    traffic_assert(true);
  }
}