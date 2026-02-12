while true do
    hardware.gpio.set_output(16, "HIGH")
    hardware.timer.delay_ms(300)
    hardware.gpio.set_output(16, "LOW")
    hardware.timer.delay_ms(300)
end