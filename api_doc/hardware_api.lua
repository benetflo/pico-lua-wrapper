--- Hardware API Module
-- Complete API for controlling Raspberry Pi Pico hardware
-- @module hardware_api

local hardware = {}

--- Reads value from given GPIO pin
-- @param pin GPIO pin number (0-22, 26-28)
-- @return 0 if LOW, 1 if HIGH
-- @usage
-- if hardware.gpio.get_input(15) == 0 then
--     print("Pin is LOW")
-- end
function gpio.get_input(pin)
    
end

return hardware