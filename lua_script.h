const char *lua_script = 
"while true do\n"
"    hardware.gpio.set_output(16, 1)\n"
"    hardware.timer.delay_ms(300)\n"
"    hardware.gpio.set_output(16, 0)\n"
"    hardware.timer.delay_ms(300)\n"
"end\n"
;
