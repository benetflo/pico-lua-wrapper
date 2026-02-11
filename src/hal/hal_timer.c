#include "hal.h"

#include "pico/stdlib.h"

void hal_timer_delay_ms (int ms)
{
    absolute_time_t until = make_timeout_time_ms(ms);
    
    while (!time_reached(until)) 
    {
        tight_loop_contents();
    }
}