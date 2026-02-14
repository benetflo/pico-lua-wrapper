hardware.uart.init()
hardware.uart.set_config("uart0", 8, 1, "NONE", false, false)

while true do
    hardware.timer.delay_ms(5000)
    hardware.uart.write_string("uart0", "Hello Simon")
    hardware.timer.delay_ms(2000)
end