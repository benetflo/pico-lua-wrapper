--- GPIO Module
-- Hardware GPIO control functions from C library
-- @module hardware.gpio

--- Reads value from given GPIO pin
-- @param pin GPIO pin number (0-22, 26-28)
-- @return 0 if LOW, 1 if HIGH
-- @usage
-- if hardware.gpio.get_input(15) == 0 then
--     print("Pin is LOW")
-- end
function get_input(pin)
end

--- Sets GPIO pin to HIGH or LOW
-- @param pin GPIO pin number (0-22, 26-28)
-- @param state "HIGH" or "LOW"
-- @usage
-- hardware.gpio.set_output(16, "HIGH")
function set_output(pin, state)
end

--- Configure GPIO pin as input
-- @param pin GPIO pin number (0-22, 26-28)
function set_input(pin)
end

--- Set pull-up or pull-down resistor
-- @param pin GPIO pin number (0-22, 26-28)
-- @param pupd "UP" or "DOWN"
function set_pulls(pin, pupd)
end