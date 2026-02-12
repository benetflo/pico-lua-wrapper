#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_libraries.h"
#include "hal.h"

static int lua_uart_init(lua_State * L)
{
    hal_uart_init(0, 1, 9600, "uart0");
    return 0;
}

void lua_open_uart_library (lua_State * L)
{
	lua_getglobal(L, "hardware");

	lua_newtable(L);

	lua_pushcfunction(L, lua_uart_init);
	lua_setfield(L, -2, "uart_init");

	lua_setfield(L, -2, "uart");

	lua_pop(L, 1);
}