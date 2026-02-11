#include "hal.h"

#include "pico/stdlib.h"

void hal_gpio_init(uint8_t pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

void hal_gpio_set_output(uint8_t pin, uint8_t value)
{
    gpio_put(pin, value);
}