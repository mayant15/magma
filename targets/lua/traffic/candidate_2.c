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
    int const2526 = 0;
    int var2550 = lua_setcstacklimit(state, const2526);
    traffic_assert(true);
    traffic_assert(true);
    int const2663 = 0;
    int var2974 = lua_rawequal(state, var431, const2663);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    int var3399 = lua_isnumber(state, var2127);
    traffic_assert(true);
    traffic_assert(true);
    int const3701 = 0;
    int var3823 = lua_gc(state, const3701);
    traffic_assert(true);
    traffic_assert(true);
    int const3876 = 0;
    int var4247 = lua_isuserdata(state, const3876);
    traffic_assert(true);
    traffic_assert(true);
    int const4610 = 0;
    int const4612 = 0;
    char* var4671 = lua_getupvalue(state, const4610, const4612);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    char out4968_slot; char* out4968 = &out4968_slot;
    int const4970 = 0;
    lua_warning(state, out4968, const4970);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    luaL_openlibs(state);
    traffic_assert(true);
    char out5675_slot; char* out5675 = &out5675_slot;
    int var5942 = lua_getglobal(state, out5675);
    traffic_assert(true);
    traffic_assert(true);
    int var6366 = lua_isnumber(state, var431);
    traffic_assert(true);
    traffic_assert(true);
    int out6439_slot; int* out6439 = &out6439_slot;
    lua_Integer var6790 = lua_tointegerx(state, const3701, out6439);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
    int const7042 = 0;
    int var7215 = lua_setiuservalue(state, const7042, const801);
    traffic_assert(true);
    traffic_assert(true);
    traffic_assert(true);
  }
}