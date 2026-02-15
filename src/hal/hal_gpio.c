#include "hal.h"
#include <string.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"


//TODO: 
//      Interrupts
//      PWM / analog output
//      Open-drain mode

static uint32_t pins_inited = 0;
static uint32_t valid_pins = 0b00001110001111111111111111111111;

uint32_t gpio_get_valid_pins(void)
{
    return valid_pins;
}

uint32_t gpio_get_pins_inited(void)
{
    return pins_inited;
}

bool gpio_is_valid(uint8_t pin) 
{
    return (pin < 32) && (valid_pins & (1u << pin));
}

void safe_gpio_init (uint8_t pin, uint8_t dir)
{
    if (!(pins_inited & (1u << pin)))
    {
        gpio_init(pin);
        pins_inited |= (1u << pin);
    }
    gpio_set_dir(pin, dir);
}

static bool is_pin_inited (uint pin) 
{
    return (pins_inited & (1u << pin)) != 0;
}

int hal_gpio_set_pulls (uint8_t pin, uint8_t pupd)
{
    if (!is_pin_inited(pin))
    {
        hal_gpio_set_input(pin); // set to input if not initialized pin is used
    }
    
    if (pupd == HAL_GPIO_PULL_UP)
    {
        gpio_pull_up(pin);
    }
    else if (pupd == HAL_GPIO_PULL_DOWN)
    {
        gpio_pull_down(pin);
    }
    else
    {
        gpio_disable_pulls(pin);
    }
    return 0;
}

void hal_gpio_set_output (uint8_t pin, uint8_t value)
{
    safe_gpio_init(pin, GPIO_OUT);
    gpio_put(pin, value);
}

void hal_gpio_set_input (uint8_t pin)
{
    safe_gpio_init(pin, GPIO_IN);
    gpio_pull_down(pin);
}

void hal_gpio_toggle (uint8_t pin)
{
    safe_gpio_init(pin, GPIO_OUT);
    gpio_xor_mask(1u << pin);
}

int hal_gpio_get_input (uint8_t pin)
{
    if (!is_pin_inited(pin))
    {    
        hal_gpio_set_input(pin);    
    }
    return gpio_get(pin);
}