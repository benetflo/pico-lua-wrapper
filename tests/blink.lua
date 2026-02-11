hardware.gpio.init(16)

while true do
    hardware.gpio.set_output(16, 1)
    hardware.timer.delay_ms(300)
    hardware.gpio.set_output(16, 0)
    hardware.timer.delay_ms(300)
end