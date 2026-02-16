-- THIS DOES NOT WORK YET

while true do
    if hardware.gpio.get_input(15) == 0 then
        hardware.gpio.set_output(16, HIGH)
    else
        hardware.gpio.set_output(16, LOW)
    end
end