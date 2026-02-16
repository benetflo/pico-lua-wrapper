--- UART Module
-- Hardware UART control functions from C library
-- @module hardware.uart


--- Sends a string from selected UART instance
-- @param uartx UART instance number (UART0, UART1)
-- @param string message to send
-- @usage
-- hardware.uart.write_string("UART0", "Hello World!")
function hardware.uart.write_string(uartx, string)
end

--- Configures the UART peripheral
--@param uartx UART instance number (UART0, UART1)
--@param data_bits Number of data bits (5-8)
--@param stop_bits Number of stop bits (1 or 2)
--@param parity Parity mode (NONE, EVEN, ODD)
--@param cts Enable CTS flow control
--@param rts Enable RTS flow control
--@usage
--hardware.uart.set_config("UART0", 8, 1, "NONE", false, false)
function hardware.uart.set_config(uartx, data_bits, stop_bits, parity, cts, rts)
end