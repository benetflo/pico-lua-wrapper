#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "lua_libraries.h"
#include "lua_script.h"
#include "hal.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"

int main () 
{
    stdio_init_all();

    lua_State * L = init_lua();
    
    if (luaL_dostring(L, lua_script) != LUA_OK) 
	{
        const char * error = lua_tostring(L, -1);
        printf("Lua error: %s\n", error);
    } 
	else 
	{
        printf("Lua script executed\n");
    }
    
    lua_close(L);
    return 0;
}