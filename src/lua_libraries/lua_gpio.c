#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_libraries.h"
#include "hal.h"
#include <stdint.h>
#include <string.h>

#include "pico/stdlib.h"


static int lua_gpio_set_output (lua_State * L)
{
	uint8_t pin = luaL_checkinteger(L, 1);
	const char * input = luaL_checkstring(L, 2);
	uint8_t value;

	if (!gpio_is_valid(pin))
	{
		luaL_error(L, "Invalid pin!");
	}

	if (strcmp(input, "HIGH") == 0)
	{
		value = GPIO_HIGH;
	}
	else if (strcmp(input, "LOW") == 0)
	{
		value = GPIO_LOW;
	}
	else
	{
		luaL_error(L, "Invalid value!");
	}
	
	hal_gpio_set_output(pin, value);
	return 0;
}

static int lua_gpio_set_input (lua_State * L)
{
	uint8_t pin = luaL_checkinteger(L, 1);
	
	if (!gpio_is_valid(pin))
	{
		luaL_error(L, "Invalid pin!");
	}

	hal_gpio_set_input(pin);

	return 0;
}

static int lua_gpio_get_input (lua_State * L)
{
	uint8_t pin = luaL_checkinteger(L, 1);
	
	if (!gpio_is_valid(pin))
	{
		luaL_error(L, "Invalid pin!");
	}
	
	int value = hal_gpio_get_input(pin);
	lua_pushinteger(L, value);
	
	return 1;
}

static int lua_gpio_set_pulls (lua_State * L)
{
	uint8_t pin = luaL_checkinteger(L, 1);
	const char * pupd = luaL_checkstring(L, 2);
	
	if (!gpio_is_valid(pin))
	{
		luaL_error(L, "Invalid pin!");
	}

	if (!(strcmp(pupd, "UP") == 0 || strcmp(pupd, "DOWN") == 0))
	{
		luaL_error(L, "Invalid pull up and pull down config!");
	}

	hal_gpio_set_pulls(pin, pupd);

	return 0;
}

void lua_open_gpio_library (lua_State * L)
{
	lua_getglobal(L, "hardware");

	lua_newtable(L);

	lua_pushcfunction(L, lua_gpio_set_output);
	lua_setfield(L, -2, "set_output");

	lua_pushcfunction(L, lua_gpio_set_input);
	lua_setfield(L, -2, "set_input");

	lua_pushcfunction(L, lua_gpio_get_input);
	lua_setfield(L, -2, "get_input");

	lua_pushcfunction(L, lua_gpio_set_pulls);
	lua_setfield(L, -2, "set_pulls");

	lua_setfield(L, -2, "gpio");

	lua_pop(L, 1);
}
