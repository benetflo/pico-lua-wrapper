#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_libraries.h"
#include "hal.h"

#include <string.h>

static int lua_uart_init (lua_State * L)
{
    hal_uart_init(0, 1, 9600, "uart0");
    return 0;
}

static int lua_uart_write_string (lua_State * L)
{
    const char * uartx = luaL_checkstring(L, 1);
    const char * data = luaL_checkstring(L, 2);

    hal_uart_write_string(uartx, data);
    
    return 0;
}

/**
 * @brief Configure UART peripheral
 * 
 * @param uart_id   UART instance identifier (uart0, uart1)
 * @param data_bits Number of data bits (5-8)
 * @param stop_bits Number of stop bits (1 or 2)
 * @param parity    Parity mode (NONE, EVEN, ODD)
 * @param cts       Enable CTS flow control
 * @param rts       Enable RTS flow control
 * 
 * @return 0 on sucess, negative value on error.    
 */
static int lua_uart_set_config (lua_State * L) // TODO: FIX THIS CLEANLY
{
    const char * uartx = luaL_checkstring(L, 1);
    if (strcmp(uartx, "uart0") != 0 &&
        strcmp(uartx, "uart1") != 0)
    {
        luaL_error(L, "Invalid UART instance");
    }

    uint8_t data_bits = luaL_checkinteger(L, 2);
    if (data_bits < 5 || data_bits > 8)
    {
        luaL_error(L, "Invalid amount of data bits chosen");
    }
    
    uint8_t stop_bits = luaL_checkinteger(L, 3);
    if (stop_bits != 1 &&
        stop_bits != 2)
    {
        luaL_error(L, "Invalid amount of stop bits chosen");
    }
    
    const char * parity = luaL_checkstring(L, 4);
    if (strcmp(parity, "NONE") != 0 &&
        strcmp(parity, "EVEN") != 0 &&
        strcmp(parity, "ODD") != 0)
    {
        luaL_error(L, "Invalid parity");
    }
    
    bool cts = lua_toboolean(L, 5);
    bool rts = lua_toboolean(L, 6);
    
    hal_uart_set_config(uartx, data_bits, stop_bits, parity, cts, rts);

    return 0;
}

void lua_open_uart_library (lua_State * L)
{
	lua_getglobal(L, "hardware");

	lua_newtable(L);

	lua_pushcfunction(L, lua_uart_init);
	lua_setfield(L, -2, "init");

    lua_pushcfunction(L, lua_uart_write_string);
	lua_setfield(L, -2, "write_string");

    lua_pushcfunction(L, lua_uart_set_config);
	lua_setfield(L, -2, "set_config");

	lua_setfield(L, -2, "uart");

	lua_pop(L, 1);
}