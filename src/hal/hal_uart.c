// hal_uart.c
#include "hal.h"

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    bool in_use;
    int tx_pin;
    int rx_pin;
    uint16_t baudrate;
    uart_inst_t * uart_num;
    uint8_t uart_id;   // NY: Identifiera UART (UART0/UART1)
} uart_instance_t;

// UART-instanser
static uart_instance_t uart0_instance = {
    .in_use = false,
    .tx_pin = -1,
    .rx_pin = -1,
    .baudrate = 0,
    .uart_num = uart0,
    .uart_id = HAL_UART_UART0
};

static uart_instance_t uart1_instance = {
    .in_use = false,
    .tx_pin = -1,
    .rx_pin = -1,
    .baudrate = 0,
    .uart_num = uart1,
    .uart_id = HAL_UART_UART1
};

// Tillåtna pins för varje UART
static uint32_t valid_uart0_tx_pins = (1U << 0) | (1U << 12) | (1U << 16);
static uint32_t valid_uart0_rx_pins = (1U << 1) | (1U << 13) | (1U << 17);
static uint32_t valid_uart1_tx_pins = (1U << 4) | (1U << 8);
static uint32_t valid_uart1_rx_pins = (1U << 5) | (1U << 9);

// Kontrollera giltig TX-pin
static bool is_valid_tx_pin(uart_instance_t * inst) {
    if (inst->uart_id == HAL_UART_UART0) 
    {
        return (valid_uart0_tx_pins & (1U << inst->tx_pin)) != 0;
    } 
    else 
    {
        return (valid_uart1_tx_pins & (1U << inst->tx_pin)) != 0;
    }
}

// Kontrollera giltig RX-pin
static bool is_valid_rx_pin(uart_instance_t * inst) {
    if (inst->uart_id == HAL_UART_UART0) 
    {
        return (valid_uart0_rx_pins & (1U << inst->rx_pin)) != 0;
    } 
    else 
    {
        return (valid_uart1_rx_pins & (1U << inst->rx_pin)) != 0;
    }
}

// Flexibel pin-check: endast kontrollera att TX och RX är giltiga
static bool uart_pins_valid(uart_instance_t * inst) 
{
    return is_valid_tx_pin(inst) && is_valid_rx_pin(inst);
}

// Fyll instans med info
static void uart_instance_fill(uart_instance_t * uartx_instance, uint8_t tx, uint8_t rx, uint16_t baudrate) 
{
    uartx_instance->tx_pin = tx;
    uartx_instance->rx_pin = rx;
    uartx_instance->baudrate = baudrate;
}


static void uart_instance_init(uart_instance_t * uartx_instance) 
{
    
    gpio_set_function(uartx_instance->tx_pin, GPIO_FUNC_UART);
    gpio_set_function(uartx_instance->rx_pin, GPIO_FUNC_UART);

    uart_init(uartx_instance->uart_num, uartx_instance->baudrate);
    uartx_instance->in_use = true;
}

hal_uart_err_t hal_uart_init(uint8_t tx, uint8_t rx, uint16_t baudrate, uint8_t uart_num) {
    
    uart_instance_t * inst;

    if (uart_num == HAL_UART_UART0) 
    {
        inst = &uart0_instance;
    } 
    else if (uart_num == HAL_UART_UART1) 
    {
        inst = &uart1_instance;
    } 
    else 
    {
        return UART_ERR_INVALID_INST;
    }

    if (inst->in_use) 
    {
        return UART_ERR_INST_IN_USE;
    }

    uart_instance_fill(inst, tx, rx, baudrate);

    if (!uart_pins_valid(inst))
    {
        return UART_ERR_INVALID_PINS;
    } 

    uart_instance_init(inst);
    
    return UART_ERR_SUCCESS;
}

int hal_uart_set_config(uint8_t uart_num, uint8_t data_bits, uint8_t stop_bits, uint16_t parity, bool cts, bool rts) {
    
    uart_instance_t * inst;

    if (uart_num == HAL_UART_UART0) 
    {
        inst = &uart0_instance;
    } 
    else if (uart_num == HAL_UART_UART1) 
    {
        inst = &uart1_instance;
    } 
    else 
    {
        return UART_ERR_INVALID_INST;
    }

    if (!inst->in_use) return UART_ERR_INST_IN_USE;

    // Parity mapping
    if (parity == HAL_UART_NONE)
    {
        parity = UART_PARITY_NONE;
    } 
        
    else if (parity == HAL_UART_EVEN)
    {
        parity = UART_PARITY_EVEN;
    }
    else 
    {
        parity = UART_PARITY_ODD;
    }
    uart_set_format(inst->uart_num, data_bits, stop_bits, parity);
    uart_set_hw_flow(inst->uart_num, cts, rts);

    return UART_ERR_SUCCESS;
}

hal_uart_err_t hal_uart_write_string(uint8_t uart_num, const char * data) {
    
    uart_instance_t * inst;

    if (uart_num == HAL_UART_UART0)
    {
        inst = &uart0_instance;
    }
    else if (uart_num == HAL_UART_UART1) 
    {
        inst = &uart1_instance;
    }
    else
    {
        return UART_ERR_INVALID_INST;
    }

    if (!inst->in_use)
    {
        return UART_ERR_INST_IN_USE;
    } 
    if (!uart_is_writable(inst->uart_num)) 
    {
        return UART_ERR_NOT_WRITABLE;
    }

    uart_puts(inst->uart_num, data);

    return UART_ERR_SUCCESS;
}