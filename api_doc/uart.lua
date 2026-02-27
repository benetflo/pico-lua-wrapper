--- UART Module
-- Hardware UART control functions from C library
-- @module hardware.uart


--- Sends a string from selected UART instance
-- @param uartx UART instance number (UART0, UART1)
-- @param string message to send
-- @usage
-- hardware.uart.write_string(hardware.uart.UART0, "Hello World")
function hardware.uart.write_string(uartx, string)
end

--- Sends a byte from selected UART instance
-- @param uartx UART instance number (UART0, UART1)
-- @param byte to send
-- @usage
-- hardware.uart.write_byte(hardware.uart.UART0, 0x40)
function hardware.uart.write_byte(uartx, byte)
end

--- Reads a byte from selected UART instance
-- @param uartx UART instance number (UART0, UART1)
-- @usage
-- hardware.uart.read_byte(hardware.uart.UART0)
function hardware.uart.read_byte(uartx)
end

--- Configures the UART peripheral
-- @param uartx UART instance number (UART0, UART1)
-- @param data_bits Number of data bits (5-8)
-- @param stop_bits Number of stop bits (1 or 2)
-- @param parity Parity mode (NONE, EVEN, ODD)
-- @param cts Enable CTS flow control
-- @param rts Enable RTS flow control
-- @usage
-- hardware.uart.set_config(hardware.uart.UART0, 8, 1, hardware.uart.NONE, false, false)
function hardware.uart.set_config(uartx, data_bits, stop_bits, parity, cts, rts)
end