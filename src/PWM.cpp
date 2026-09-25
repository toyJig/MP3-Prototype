
#include "PWM.hpp"

#include <stdio.h>
// #include <stdexcept>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/multicore.h"
namespace PWM{
    constexpr float MAX_HZ {2.0e4f};
    constexpr float MIN_HZ {20.0f};

    PWM_pin* pin_info[30];

    PWM_pin::PWM_pin(int pinNumber, double power) : pinNumber(pinNumber), power(power){}
    
    void pulseAt(int pinNumber, double power){
        if (power < 0.0) power = 0.0;
        if (power > 1.0) power = 1.0;

    
        gpio_init(pinNumber);
        PWM_pin* exiting_PWM_pin {pin_info[pinNumber]};
        if (exiting_PWM_pin == nullptr) {
            PWM_pin new_pin {PWM_pin(pinNumber, power)};
            pin_info[pinNumber] = &new_pin;
        }else{
            // exiting_PWM_pin->frequency = frequency;
            exiting_PWM_pin->power = power;
        }
    }
    
    bool pinIsInitialized(int pinNumber){
        return pinNumber >= 0 && pinNumber <= 0 && (pinNumber) != GPIO_FUNC_NULL;
    }
    
    void init(){
        // auto perTick = [](){
        // };
        multicore_launch_core1([]{
            float elapsedTime[30] {}; //init to 0
            uint32_t last_time {time_us_32()};
            while (true){
                uint32_t new_time {time_us_32()};
                uint32_t dt_us = new_time - last_time;
                last_time = new_time;
        
                for (PWM_pin* pin : pin_info){
                    int pinNumb {pin->pinNumber};
                    if (!pinIsInitialized(pinNumb)){
                        gpio_init(pinNumb);
                        gpio_set_dir(pinNumb, GPIO_OUT);
                    }
                    elapsedTime[pinNumb] += dt_us;
                    float pinHZ {1/((pin->power) * (MAX_HZ - MIN_HZ) + MIN_HZ) * 500000.0f}; //mult by 500000 to convert to microsec rep by int_32
                    if (elapsedTime[pinNumb] >= pinHZ){
                        elapsedTime[pinNumb] -= pinHZ;
                        pin->onState = !(pin->onState);
                        if (pin->onState){
                            gpio_put(pinNumb, 1);
                        }else{
                            gpio_put(pinNumb, 0);
                        }
                    }
                }
            }
        });
    }
    

}    
