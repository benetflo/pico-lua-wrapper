hardware.gpio.set_input(15)
hardware.gpio.set_pulls(15, hardware.gpio.UP)

while true do
    if hardware.gpio.get_input(15) == 0 then
        hardware.gpio.set_output(16, hardware.gpio.HIGH)
    else
        hardware.gpio.set_output(16, hardware.gpio.LOW)
    end
end