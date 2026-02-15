#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_libraries.h"
#include "hal.h"
#include <stdint.h>
#include <string.h>

#include "pico/stdlib.h"


static int lua_gpio_init (lua_State * L)
{
	uint8_t pin = luaL_checkinteger(L, 1);
	uint8_t dir = luaL_checkinteger(L, 2);

	if (!gpio_is_valid(pin))
	{
		luaL_error(L, "Invalid pin!");
	}

	if (dir != GPIO_OUT &&
		dir != GPIO_IN)
	{
		luaL_error(L, "Invalid GPIO direction");
	}

	safe_gpio_init(pin, dir);
	
	return 0;
}

static int lua_gpio_set_output (lua_State * L)
{
	uint8_t pin = luaL_checkinteger(L, 1);
	uint8_t value = luaL_checkinteger(L, 2);

	if (!gpio_is_valid(pin))
	{
		luaL_error(L, "Invalid pin!");
	}

	if (value != HAL_GPIO_HIGH &&
		value != HAL_GPIO_LOW)
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

static int lua_gpio_toggle (lua_State * L)
{
	uint8_t pin = luaL_checkinteger(L, 1);

	if (!gpio_is_valid(pin))
	{
		luaL_error(L, "Invalid pin!");
	}

	hal_gpio_toggle(pin);

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
	uint8_t pupd = luaL_checkinteger(L, 2);
	
	if (!gpio_is_valid(pin))
	{
		luaL_error(L, "Invalid pin!");
	}

	if (pupd != HAL_GPIO_PULL_UP  && 
		pupd != HAL_GPIO_PULL_DOWN &&
		pupd != HAL_GPIO_PULL_NONE)
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

	lua_pushinteger(L, GPIO_OUT);
	lua_setfield(L, -2, "OUT");

	lua_pushinteger(L, GPIO_IN);
	lua_setfield(L, -2, "IN");

    // Output levels
    lua_pushinteger(L, HAL_GPIO_HIGH);
    lua_setfield(L, -2, "HIGH");

    lua_pushinteger(L, HAL_GPIO_LOW);
    lua_setfield(L, -2, "LOW");

    // Pull types
    lua_pushinteger(L, HAL_GPIO_PULL_UP);
    lua_setfield(L, -2, "UP");

    lua_pushinteger(L, HAL_GPIO_PULL_DOWN);
    lua_setfield(L, -2, "DOWN");

	lua_pushinteger(L, HAL_GPIO_PULL_NONE);
    lua_setfield(L, -2, "NONE");

	lua_pushcfunction(L, lua_gpio_init);
	lua_setfield(L, -2, "init");

	lua_pushcfunction(L, lua_gpio_set_output);
	lua_setfield(L, -2, "set_output");

	lua_pushcfunction(L, lua_gpio_set_input);
	lua_setfield(L, -2, "set_input");

	lua_pushcfunction(L, lua_gpio_toggle);
	lua_setfield(L, -2, "toggle");

	lua_pushcfunction(L, lua_gpio_get_input);
	lua_setfield(L, -2, "get_input");

	lua_pushcfunction(L, lua_gpio_set_pulls);
	lua_setfield(L, -2, "set_pulls");

	lua_setfield(L, -2, "gpio");

	lua_pop(L, 1);
}
