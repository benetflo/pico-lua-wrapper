function check_input(test, result, expected)
    if tonumber(string.format("%.1f", result)) == expected then
        print("PASSED - " .. test)
    else
        local msg = "FAILED - " .. test .. ". Expected: " .. tostring(expected) .. ", got: " .. tostring(result)
        print(msg)
    end
end

function gpio_output_test()

    -- Test GPIO out
    print("Setting pin 2 HIGH")
    hardware.gpio.set_output(2, "HIGH")
    
    hardware.timer.delay_ms(2000)

    check_input("Pin 3 is HIGH", 
        hardware.gpio.get_input(3),
        1)

end

function gpio_input_test()
    
    -- Test GPIO in and PUPD
    print("Setting PULL UP on pin 0")
    hardware.gpio.set_pulls(0, "UP")
   
    hardware.timer.delay_ms(2000)
    
    check_input("Pin 0 is pulled up",
        hardware.gpio.get_input(0),
        1)
    
    hardware.timer.delay_ms(2000)

    print("Setting PULL DOWN on pin 0")
    hardware.gpio.set_pulls(0, "DOWN")
    
    hardware.timer.delay_ms(2000)
    
    check_input("Pin 0 is pulled down",
        hardware.gpio.get_input(0),
        0)
end

while true do
    
    print("Running GPIO tests...")
    hardware.timer.delay_ms(5000)

    print("Running output tests")
    gpio_output_test()
    
    hardware.timer.delay_ms(2000)
    
    print("Running input tests")
    gpio_input_test()

end