#include "hal.h"

#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <stdio.h>

static uint32_t valid_uart0_tx_pins = (1 << 0) | (1 << 12) | (1 << 16);
static uint32_t valid_uart0_rx_pins = (1 << 1) | (1 << 13) | (1 << 17);

static uint32_t valid_uart1_tx_pins = (1 << 4) | (1 << 8);
static uint32_t valid_uart1_rx_pins = (1 << 5) | (1 << 9);


static bool is_valid_tx_pin (uart_instance_t * inst)
{
    if (inst->uart_num == uart0)
    {
        return (valid_uart0_tx_pins & (1 << inst->tx_pin)) != 0;
    }
    
    return (valid_uart1_tx_pins & (1 << inst->tx_pin)) != 0;
}

static bool is_valid_rx_pin (uart_instance_t * inst)
{
    if (inst->uart_num == uart0)
    {
        return (valid_uart0_rx_pins & (1 << inst->rx_pin)) != 0;
    }
    
    return (valid_uart1_rx_pins & (1 << inst->rx_pin)) != 0;
}

static bool uart_pins_valid (uart_instance_t * inst)
{
    if (!is_valid_tx_pin(inst))
        return false;
    if (!is_valid_rx_pin(inst))
        return false;

    if (inst->uart_num == uart0)
    {
        if ((inst->tx_pin == 0 && inst->rx_pin != 1) &&
            (inst->tx_pin == 12 && inst->rx_pin != 13) &&
            (inst->tx_pin == 16 && inst->rx_pin != 17))
        {
            return false;
        }
    }
    else if (inst->uart_num == uart1)
    {
        if ((inst->tx_pin == 4 && inst->rx_pin != 5) &&
            (inst->tx_pin == 8 && inst->rx_pin != 9))
        {
            return false;
        }
    }

    return true;
}

typedef struct {
    bool in_use;
    int tx_pin;
    int rx_pin;
    uint16_t baudrate;
    uart_inst_t * uart_num;
} uart_instance_t;

static uart_instance_t uart0_instance =
{
    .in_use = false,
    .tx_pin = -1,
    .rx_pin = -1,
    .baudrate = 0,
    .uart_num = uart0
};
static uart_instance_t uart1_instance =
{
    .in_use = false,
    .tx_pin = -1,
    .rx_pin = -1,
    .baudrate = 0,
    .uart_num = uart1
};

static void uart_instance_fill (uart_instance_t * uartx_instance, uint8_t tx, uint8_t rx, uint16_t baudrate)
{
    uartx_instance->tx_pin = tx;
    uartx_instance->rx_pin = rx;
    uartx_instance->baudrate = baudrate;
}

static void uart_instance_init (uart_instance_t * uartx_instance)
{
    gpio_set_function(uartx_instance->tx_pin, GPIO_FUNC_UART);
    gpio_set_function(uartx_instance->rx_pin, GPIO_FUNC_UART);

    uart_init(uartx_instance->uart_num, uartx_instance->baudrate);
    uartx_instance->in_use = true;
}

int hal_uart_init(uint8_t tx, uint8_t rx, uint16_t baudrate, const char * uart_num)
{

    if (strcmp(uart_num, "uart0") == 0)
    {
        if (uart0_instance.in_use)
        {
            return -2;
        }

        uart_instance_fill(&uart0_instance, tx, rx, baudrate);
        
        if(!uart_pins_valid(&uart0_instance))
        {
            return -1;
        }
        uart_instance_init(&uart0_instance);
    }
    else
    {
        if (uart1_instance.in_use)
        {
            return -2;
        }
        
        uart_instance_fill(&uart1_instance, tx, rx, baudrate);
        
        if(!uart_pins_valid(&uart1_instance))
        {
            return -1;
        }
        uart_instance_init(&uart1_instance);
    }
    
    return 0;
}