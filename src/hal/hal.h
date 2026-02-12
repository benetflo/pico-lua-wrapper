#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include <stdbool.h>

//#define UINT32_MAX          4294967295U

// MACHINE
void hal_core1_main(void);
void hal_machine_launch_core1(void);

// GPIO
#define GPIO_HIGH                1
#define GPIO_LOW                 0

bool gpio_is_valid(uint8_t pin);
void hal_gpio_set_output(uint8_t pin, uint8_t value);
void hal_gpio_set_input(uint8_t pin);
int hal_gpio_get_input(uint8_t pin);
int hal_gpio_set_pulls (uint8_t pin, const char * pupd);

// TIMER
void hal_timer_delay_ms(int ms);

#endif