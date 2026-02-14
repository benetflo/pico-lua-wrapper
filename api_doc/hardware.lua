--- Hardware API Module
-- This is the Lua interface to the C hardware library
-- Functions are registered by the C layer at hardware.gpio
-- @module hardware_api

--- GPIO Module
-- GPIO control functions from C library
-- @section gpio

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
-- hardware.gpio.set_output(16, "HIGH")
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
-- @param pupd "UP" or "DOWN"
-- @usage
-- hardware.gpio.set_pulls(15, "UP")
function hardware.gpio.set_pulls(pin, pupd)
end