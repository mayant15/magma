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
    int const2175 = 0;
    int var2550 = lua_isinteger(state, const2175);
    traffic_assert(true);
    traffic_assert(true);
    int const2661 = 0;
    int const2663 = 0;
    int var2974 = lua_rawequal(state, const2661, const2663);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    int* null3043 = NULL;
    lua_Number var3399 = lua_tonumberx(state, const2175, null3043);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    int const3519 = 0;
    int const3521 = 0;
    int var3824 = lua_compare(state, const801, const3519, const3521);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    int var4250 = lua_isstring(state, var2974);
    traffic_assert(true);
    traffic_assert(true);
  }
}