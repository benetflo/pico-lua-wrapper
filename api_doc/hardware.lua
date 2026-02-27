--- Hardware API Module
-- This is the Lua interface to the C hardware library
-- Functions are registered by the C layer at hardware.gpio
-- @module hardware_api

--- GPIO Module
-- GPIO control functions from C library
-- @section gpio

--- Initializes GPIO pin.
-- Binding to: lua_gpio_init (C function)
-- @param pin GPIO pin number (0-22, 26-28)
-- @usage
-- hardware.gpio.init(16)
function hardware.gpio.init(pin)
end

--- Reads value from given GPIO pin
-- Binding to: lua_gpio_get_input (C function)
-- @param pin GPIO pin number (0-22, 26-28)
-- @return 0 if LOW, 1 if HIGH
-- @usage
-- if hardware.gpio.get_input(15) == 0 then
--     print("Pin is LOW")
-- end
function hardware.gpio.get_input(pin)
end

--- Sets GPIO pin to HIGH or LOW
-- Binding to: lua_gpio_set_output (C function)
-- @param pin GPIO pin number (0-22, 26-28)
-- @param state "HIGH" or "LOW"
-- @usage
-- hardware.gpio.set_output(16, hardware.gpio.HIGH)
function hardware.gpio.set_output(pin, state)
end

--- Configure GPIO pin as input
-- Binding to: lua_gpio_set_input (C function)
-- @param pin GPIO pin number (0-22, 26-28)
-- @usage
-- hardware.gpio.set_input(15)
function hardware.gpio.set_input(pin)
end

--- Set pull-up or pull-down resistor
-- Binding to: lua_gpio_set_pulls (C function)
-- @param pin GPIO pin number (0-22, 26-28)
-- @param pupd "UP", "DOWN" or "NONE"
-- @usage
-- hardware.gpio.set_pulls(15, hardware.gpio.UP))
function hardware.gpio.set_pulls(pin, pupd)
end

--- UART Module
-- UART serial communication functions from C library
-- @section uart

--- Sends a string from selected UART instance
-- Binding to: lua_uart_write_string (C function)
-- @param uartx UART instance number (UART0, UART1)
-- @param string message to send
-- @usage
-- hardware.uart.write_string("UART0", "Hello World!")
function hardware.uart.write_string(uartx, string)
end

--- Sends a byte from selected UART instance
-- Binding to: lua_uart_write_byte (C function)
-- @param uartx UART instance number (UART0, UART1)
-- @param byte to send
-- @usage
-- hardware.uart.write_byte(hardware.uart.UART0, 0x40)
function hardware.uart.write_byte(uartx, byte)
end

--- Reads a byte from selected UART instance
-- Binding to: lua_uart_read_byte (C function)
-- @param uartx UART instance number (UART0, UART1)
-- @usage
-- hardware.uart.read_byte(hardware.uart.UART0)
function hardware.uart.read_byte(uartx)
end

--- Configures the UART peripheral
-- @param uartx UART instance number (UART0, UART1)
-- @param data_bits Number of data bits (5-8)
-- @param stop_bits Number of stop bits (1 or 2)
-- @param parity Parity mode (NONE, EVEN, ODD)
-- @param cts Enable CTS flow control
-- @param rts Enable RTS flow control
-- @usage
-- hardware.uart.set_config("UART0", 8, 1, "NONE", false, false)
function hardware.uart.set_config(uartx, data_bits, stop_bits, parity, cts, rts)
end