#include "hal.h"

#include "pico/stdlib.h"

static uint32_t pins_inited = 0;

static void safe_gpio_init (uint8_t pin, uint8_t dir)
{
    if (!(pins_inited & (1u << pin)))
    {
        gpio_init(pin);
        gpio_set_dir(pin, dir);
        pins_inited |= (1u << pin);
    }
}

static bool is_pin_inited (uint pin) 
{
    return (pins_inited & (1u << pin)) != 0;
}

void hal_gpio_set_output (uint8_t pin, uint8_t value)
{
    safe_gpio_init(pin, GPIO_OUT);
    gpio_put(pin, value);
}

void hal_gpio_set_input (uint8_t pin)
{
    safe_gpio_init(pin, GPIO_IN);
    gpio_pull_up(pin);
}

int hal_gpio_get_input (uint8_t pin)
{
    if (!is_pin_inited(pin))
    {    
        hal_gpio_set_input(pin);    
    }
    return gpio_get(pin);
}