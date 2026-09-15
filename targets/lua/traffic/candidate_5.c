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
    char* null3947 = NULL;
    int const3948 = 0;
    char* var4242 = lua_pushlstring(state, null3947, const3948);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    lua_State* null4525 = NULL;
    int out4528_slot; int* out4528 = &out4528_slot;
    int var4667 = lua_resume(state, null4525, var431, out4528);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    int const4760 = 0;
    lua_CFunction var5093 = lua_tocfunction(state, const4760);
    traffic_assert(true);
    traffic_assert(true);
    int var5519 = luaopen_string(state);
    traffic_assert(true);
    lua_State* null5864 = NULL;
    char out5865_slot; char* out5865 = &out5865_slot;
    lua_Debug out5867_slot; lua_Debug* out5867 = &out5867_slot;
    int var5944 = lua_getinfo(null5864, out5865, out5867);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
  }
}