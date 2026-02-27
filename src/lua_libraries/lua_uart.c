#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_libraries.h"
#include "hal.h"

#include <string.h>

static int lua_uart_init (lua_State * L)
{
    uint8_t tx_pin = luaL_checkinteger(L, 1);
    uint8_t rx_pin = luaL_checkinteger(L, 2);
    uint16_t baudrate = luaL_checkinteger(L, 3);
    uint8_t uartx = luaL_checkinteger(L, 4);
    
    int result = hal_uart_init(tx_pin, rx_pin, baudrate, uartx);
    
    if (result == UART_ERR_INVALID_PINS) 
    {
        luaL_error(L, "Invalid TX and or RX pins");
    }
    else if (result == UART_ERR_INST_IN_USE) 
    {
        luaL_error(L, "Instance already in use");
    }
    
    return 0;
}

static int lua_uart_write_string (lua_State * L)
{
    uint8_t uartx = luaL_checkinteger(L, 1);

    if (uartx != HAL_UART_UART0 &&
        uartx != HAL_UART_UART1)
    {
        luaL_error(L, "Invalid UART instance");
    }

    const char * data = luaL_checkstring(L, 2); // TODO: might need to null terminate here

    int result = hal_uart_write_string(uartx, data);

    if (result == UART_ERR_INVALID_INST)
    {
        luaL_error(L, "Invalid UART instance");
    }
    else if (result == UART_ERR_INST_IN_USE)
    {
        luaL_error(L, "UART not initialized");
    }
    else if (result == UART_ERR_NOT_WRITABLE)
    {
        luaL_error(L, "UART not writable");
    }

    
    return 0;
}

static int lua_uart_write_byte (lua_State * L)
{
    uint8_t uartx = luaL_checkinteger(L, 1);

    if (uartx != HAL_UART_UART0 &&
        uartx != HAL_UART_UART1)
    {
        luaL_error(L, "Invalid UART instance");
    }

    lua_Integer li = luaL_checkinteger(L, 2);
    if (li < 0 || li > 255)
    {
        luaL_error(L, "Byte out of range");
    }
    char c = (char)li;

    int result = hal_uart_write_byte(uartx, c);

    if (result == UART_ERR_INVALID_INST)
    {
        luaL_error(L, "Invalid UART instance");
    }
    else if (result == UART_ERR_INST_IN_USE)
    {
        luaL_error(L, "UART not initialized");
    }
    else if (result == UART_ERR_NOT_WRITABLE)
    {
        luaL_error(L, "UART not writable");
    }

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
static int lua_uart_set_config (lua_State * L)
{
    uint8_t uartx = luaL_checkinteger(L, 1);
    if (uartx != HAL_UART_UART0 &&
        uartx != HAL_UART_UART1)
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
    
    uint8_t parity = luaL_checkinteger(L, 4);
    if (parity != HAL_UART_NONE &&
        parity != HAL_UART_EVEN &&
        parity != HAL_UART_ODD)
    {
        luaL_error(L, "Invalid parity");
    }
    
    bool cts = lua_toboolean(L, 5);
    bool rts = lua_toboolean(L, 6);
    
    int result = hal_uart_set_config(uartx, data_bits, stop_bits, parity, cts, rts);

    if (result == UART_ERR_INVALID_INST)
    {
        luaL_error(L, "Invalid UART instance");
    }
    else if (result == UART_ERR_INST_IN_USE)
    {
        luaL_error(L, "UART not initialized");
    }

    return 0;
}

void lua_open_uart_library (lua_State * L)
{
	lua_getglobal(L, "hardware");

	lua_newtable(L);

    lua_pushinteger(L, HAL_UART_NONE);
    lua_setfield(L, -2, "NONE");

    lua_pushinteger(L, HAL_UART_EVEN);
    lua_setfield(L, -2, "EVEN");

    lua_pushinteger(L, HAL_UART_ODD);
    lua_setfield(L, -2, "ODD");

    lua_pushinteger(L, HAL_UART_UART0);
    lua_setfield(L, -2, "UART0");

    lua_pushinteger(L, HAL_UART_UART1);
    lua_setfield(L, -2, "UART1");

	lua_pushcfunction(L, lua_uart_init);
	lua_setfield(L, -2, "init");

    lua_pushcfunction(L, lua_uart_write_string);
	lua_setfield(L, -2, "write_string");

    lua_pushcfunction(L, lua_uart_write_byte);
	lua_setfield(L, -2, "write_byte");

    lua_pushcfunction(L, lua_uart_set_config);
	lua_setfield(L, -2, "set_config");

	lua_setfield(L, -2, "uart");

	lua_pop(L, 1);
}