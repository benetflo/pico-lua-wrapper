#ifndef LUA_LIBRARIES_H
#define LUA_LIBRARIES_H

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

lua_State * init_lua (void);

// GPIO
void lua_open_gpio_library(lua_State * L);
void lua_open_timer_library(lua_State * L);
void lua_open_uart_library(lua_State * L);

#endif