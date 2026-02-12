#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_libraries.h"
#include "hal.h"

static int lua_delay(lua_State * L)
{
    lua_Integer input = luaL_checkinteger(L, 1);
    
	if (input < 0 || input > UINT32_MAX)
	{
		luaL_error(L, "Invalid input");
	}

	uint32_t ms = (uint32_t)input;

    hal_timer_delay_ms(ms);

    return 0;
}

void lua_open_timer_library (lua_State * L)
{
	lua_getglobal(L, "hardware");

	lua_newtable(L);

	lua_pushcfunction(L, lua_delay);
	lua_setfield(L, -2, "delay_ms");

	lua_setfield(L, -2, "timer");

	lua_pop(L, 1);
}