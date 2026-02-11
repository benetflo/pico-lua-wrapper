while true do

    if hardware.gpio.get_input(15) == 0 then
        hardware.gpio.set_output(16, 1)
    else
        hardware.gpio.set_output(16, 0)
    end
end