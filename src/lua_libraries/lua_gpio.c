#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_libraries.h"
#include "hal.h"

#include "pico/stdlib.h"

#include <stdint.h>

static int lua_gpio_init(lua_State * L)
{
	uint8_t pin = luaL_checkinteger(L, 1);
	printf("lua_gpio_init called with pin %d\n", pin);
	hal_gpio_init(pin);
	printf("hal_gpio_init completed\n");
	return 0;
}

static int lua_gpio_set_output (lua_State * L)
{
	printf("lua_gpio_set_output called!\n");
	uint8_t pin = luaL_checkinteger(L, 1);
	uint8_t value = luaL_checkinteger(L, 2);
	printf("Setting pin %d to %d\n", pin, value);
	hal_gpio_set_output(pin, value);
	return 0;
}



void lua_open_gpio_library (lua_State * L)
{
	lua_getglobal(L, "hardware");

	lua_newtable(L);

	lua_pushcfunction(L, lua_gpio_set_output);
	lua_setfield(L, -2, "set_output");

	lua_pushcfunction(L, lua_gpio_init);
	lua_setfield(L, -2, "init");

	lua_setfield(L, -2, "gpio");

	lua_pop(L, 1);
}
