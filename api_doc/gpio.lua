--- GPIO Module
-- Hardware GPIO control functions from C library
-- @module hardware.gpio

-- Initializes GPIO pin.
-- @param pin GPIO pin number (0-22, 26-28)
-- @usage
-- hardware.gpio.init(16)
function init(pin)
end

--- Sets GPIO pin to HIGH or LOW. Init is done automatically.
-- @param pin GPIO pin number (0-22, 26-28)
-- @param state "HIGH" or "LOW"
-- @usage
-- hardware.gpio.set_output(16, hardware.gpio.HIGH)
function set_output(pin, state)
end

--- Configure GPIO pin as input with pull down as default. Init is done automatically.
-- @param pin GPIO pin number (0-22, 26-28) 
function set_input(pin)
end

--- Reads value from given GPIO pin
-- @param pin GPIO pin number (0-22, 26-28)
-- @return 0 if LOW, 1 if HIGH
-- @usage
-- if hardware.gpio.get_input(15) == 0 then
--     print("Pin is LOW")
-- end
function get_input(pin)
end

--- Set pull-up or pull-down resistor
-- @param pin GPIO pin number (0-22, 26-28)
-- @param pupd "UP", "DOWN" or "NONE"
-- @usage
-- hardware.gpio.set_pulls(15, hardware.gpio.UP))
function set_pulls(pin, pupd)
end