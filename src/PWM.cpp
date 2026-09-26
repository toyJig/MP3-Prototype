
#include "PWM.hpp"

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/multicore.h"
namespace PWM{
    constexpr float MAX_HZ {2.0e4f};
    constexpr float MIN_HZ {0.0e-8f};

    PWM_pin* pin_info[30];

    PWM_pin::PWM_pin(int pinNumber, double Hz, double onPercent) : pinNumber(pinNumber), Hz(Hz), onPercent(onPercent){}
    PWM_pin::PWM_pin(int pinNumber, double Hz) : pinNumber(pinNumber), Hz(Hz){}
    
    double percentHzToHz(double percent){
        return percent * (MAX_HZ - MIN_HZ) + MIN_HZ; //mult by 1e6 in order to convert us to s                                                                               
    }
    
    void pulseAtHz(int pinNumber, double Hz, double onPercent){
        if (Hz < MIN_HZ) Hz = MIN_HZ;
        if (Hz > MAX_HZ) Hz = MAX_HZ;
        if (pinNumber < 0 || pinNumber >= 30){
            return;
        }
        PWM_pin* PWM_pin_info {pin_info[pinNumber]};
        if (PWM_pin_info == nullptr) {
            pin_info[pinNumber] = new PWM_pin(pinNumber, Hz, onPercent);
            gpio_init(pinNumber);
            gpio_set_dir(pinNumber, GPIO_OUT);
        }else{
            PWM_pin_info->Hz = Hz;
            PWM_pin_info->onPercent = onPercent;
        }
    }

    void pulseAtPercentHz(int pinNumber, double percent, double onPercent){
        if (percent < 0.0) percent = 0.0;
        if (percent > 1.0) percent = 1.0;
        if (pinNumber < 0 || pinNumber >= 30){
            return;
        }
        PWM_pin* PWM_pin_info {pin_info[pinNumber]};
        if (PWM_pin_info == nullptr) {
            pin_info[pinNumber] = new PWM_pin(pinNumber, percentHzToHz(percent), onPercent);
            gpio_init(pinNumber);
            gpio_set_dir(pinNumber, GPIO_OUT);
        }else{
            PWM_pin_info->Hz = percentHzToHz(percent);
            PWM_pin_info->onPercent = onPercent;
        }
    }

    
    bool pinIsInitialized(int pinNumber){
        //30 = max pins on board
        return pinNumber >= 0 && pinNumber < 30 && 
        (pin_info[pinNumber] != nullptr || (pinNumber) != GPIO_FUNC_NULL);
    }
    
    void init(){
        multicore_launch_core1([]{
            double elapsedTime[30] {}; //init to 0
            uint32_t last_time {time_us_32()};
            while (true){
                uint32_t new_time {time_us_32()};
                uint32_t dt_us = new_time - last_time;
                last_time = new_time;
        
                for (PWM_pin* pin : pin_info){
                    if (pin == nullptr || pin->onPercent == 0){ continue; }
                    int pinNumb {pin->pinNumber};
                    elapsedTime[pinNumb] += dt_us;
                    double us_pinON {1/(pin->Hz) * (pin->onPercent) * 1.0e6};
                    double us_pinOFF {1/(pin->Hz) * 1.0e6 - us_pinON};

                    if (pin->onState && elapsedTime[pinNumb] >= us_pinON){
                        elapsedTime[pinNumb] -= us_pinON;
                        pin->onState = false;
                        gpio_put(pinNumb, 0);
                    }else if (!(pin->onState) && elapsedTime[pinNumb] >= us_pinOFF){
                        elapsedTime[pinNumb] -= us_pinOFF;
                        pin->onState = true;
                        gpio_put(pinNumb, 1);
                    }
                }
            }
        });
    }
    

}    
