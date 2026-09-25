
#include "FrequencyGen.hpp"

#include <stdio.h>
// #include <stdexcept>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/multicore.h"
namespace FrequencyGen{
    constexpr float MAX_HZ {2.0e4f};
    constexpr float MIN_HZ {0.0e-5f};

    Frequency_pin* pin_info[30];

    Frequency_pin::Frequency_pin(int pinNumber, double power) : pinNumber(pinNumber), power(power){}
    
    void pulseAt(int pinNumber, double power){
        if (power < 0.0) power = 0.0;
        if (power > 1.0) power = 1.0;
        if (pinNumber < 0 || pinNumber >= 30){
            return;
        }
 
        Frequency_pin* freqPin_info {pin_info[pinNumber]};
        if (freqPin_info == nullptr) {
            pin_info[pinNumber] = new Frequency_pin(pinNumber, power);
            gpio_init(pinNumber);
            gpio_set_dir(pinNumber, GPIO_OUT);
        }else{
            freqPin_info->power = power;
        }
    }
    
    bool pinIsInitialized(int pinNumber){
        //30 = max pins on board
        return pinNumber >= 0 && pinNumber < 30 && 
        (pin_info[pinNumber] != nullptr || (pinNumber) != GPIO_FUNC_NULL);
    }
    
    void init(){
        multicore_launch_core1([]{
            float elapsedTime[30] {}; //init to 0
            uint32_t last_time {time_us_32()};
            while (true){
                uint32_t new_time {time_us_32()};
                uint32_t dt_us = new_time - last_time;
                last_time = new_time;
        
                for (Frequency_pin* pin : pin_info){
                    if (pin == nullptr){ continue; }
                    int pinNumb {pin->pinNumber};
                    elapsedTime[pinNumb] += dt_us;
                    float halfPinHZ {1/((pin->power) * (MAX_HZ - MIN_HZ) + MIN_HZ) * 500000.0f}; //mult by 500000 to convert to microsec rep by int_32
                    if (elapsedTime[pinNumb] >= halfPinHZ){
                        elapsedTime[pinNumb] -= halfPinHZ;
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
