#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <stdbool.h>

//#define UINT32_MAX          4294967295U

// GPIO
typedef enum 
{
    HAL_GPIO_LOW = 0,
    HAL_GPIO_HIGH = 1
} hal_gpio_level_t;

typedef enum 
{
    HAL_GPIO_PULL_DOWN = 0,
    HAL_GPIO_PULL_UP = 1,
    HAL_GPIO_PULL_NONE = 2
} hal_gpio_pull_t;

void safe_gpio_init (uint8_t pin, uint8_t dir);
bool gpio_is_valid(uint8_t pin);
void hal_gpio_set_output(uint8_t pin, uint8_t value);
void hal_gpio_set_input(uint8_t pin);
int hal_gpio_get_input(uint8_t pin);
void hal_gpio_toggle(uint8_t pin);
int hal_gpio_set_pulls (uint8_t pin, uint8_t pupd);

// UART

typedef enum 
{
    HAL_UART_EVEN = 0,
    HAL_UART_ODD = 1,
    HAL_UART_NONE = 2
} hal_uart_parity_t;

typedef enum
{
    HAL_UART_UART0 = 0,
    HAL_UART_UART1 = 1
} hal_uart_uartx_t;

int hal_uart_init(uint8_t tx, uint8_t rx, uint16_t baudrate, const char * uart_num);
int hal_uart_set_config (const char * uart_num, uint8_t data_bits, uint8_t stop_bits, const char * parity, bool cts, bool rts);
int hal_uart_write_string (const char * uart_num, const char * data);


// TIMER
void hal_timer_delay_ms(int ms);

#endif