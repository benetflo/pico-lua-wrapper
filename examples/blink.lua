while true do
    hardware.gpio.set_output(16, hardware.gpio.HIGH)
    hardware.timer.delay_ms(300)
    hardware.gpio.set_output(16, hardware.gpio.LOW)
    hardware.timer.delay_ms(300)
end