#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_libraries.h"


lua_State * init_lua (void)
{
	lua_State * L = luaL_newstate();

	luaL_openlibs(L);

	lua_newtable(L);
	lua_setglobal(L, "hardware");

	lua_open_gpio_library(L);
	lua_open_timer_library(L);
	lua_open_uart_library(L);

	return L;
}
