hardware.gpio.toggle(16)

while true do
    hardware.timer.delay_ms(2000)
    hardware.gpio.toggle(16)
end