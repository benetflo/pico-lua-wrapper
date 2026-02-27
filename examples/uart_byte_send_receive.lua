hardware.uart.init(0, 1, 9600, hardware.uart.UART0)
hardware.uart.set_config(hardware.uart.UART0, 8, 1, hardware.uart.NONE, false, false)

hardware.uart.init(4, 5, 9600, hardware.uart.UART1)
hardware.uart.set_config(hardware.uart.UART1, 8, 1, hardware.uart.NONE, false, false)

while true do
    hardware.timer.delay_ms(5000)
    hardware.uart.write_byte(hardware.uart.UART0, 0x40)
    
    local byte = hardware.uart.read_byte(hardware.uart.UART1)
    if byte == 0x40 then
        hardware.gpio.set_output(16, hardware.gpio.HIGH)
    end
    
    hardware.timer.delay_ms(2000)
    hardware.gpio.set_output(16, hardware.gpio.LOW)
end