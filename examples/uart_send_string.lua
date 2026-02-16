hardware.uart.init(0, 13, 9600, hardware.uart.UART0)
hardware.uart.set_config(hardware.uart.UART0, 8, 1, hardware.uart.NONE, false, false)

while true do
    hardware.timer.delay_ms(5000)
    hardware.uart.write_string(hardware.uart.UART0, "Hello Simon")
    hardware.timer.delay_ms(2000)
end