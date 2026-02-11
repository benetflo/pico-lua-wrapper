#ifndef HAL_H
#define HAL_H

#include <stdint.h>

// GPIO
void hal_gpio_init(uint8_t pin);
void hal_gpio_set_output(uint8_t pin, uint8_t value);
void hal_timer_delay_ms(int ms);

#endif