
#include "PWM.hpp"

#include <stdio.h>
// #include <stdexcept>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "pico/multicore.h"

class PWM_pin {
    public:
        int frequency;
        int power;
        int pinNumber;
        // bool enabled;
        PWM_pin(int pinNumber, int frequency, int power) : pinNumber(pinNumber), frequency(frequency), power(power){}
};

PWM_pin* pin_info[30];

int MIN_VOLTAGE = 0;
int MAX_VOLTAGE = 3.3;
void pulseAt(int pinNumber, int frequency, double power){
    // if (power > 100 || power < 0){
    //     throw std::out_of_range("Out of power bounds. Please provide value (0-100)");
    // }
    //throw error doesnt seem to work rn look into later

    gpio_init(pinNumber);
    PWM_pin* exiting_PWM_pin {pin_info[pinNumber]};
    if (exiting_PWM_pin == nullptr) {
        PWM_pin new_pin = PWM_pin(pinNumber, frequency, power);
        pin_info[pinNumber] = &new_pin;
    }else{
        exiting_PWM_pin->frequency = frequency;
        exiting_PWM_pin->power = power;
    }
}

bool pinIsInitialized(int pinNumber){
    return gpio_get_function(pinNumber) != GPIO_FUNC_NULL;
}

void pulseAll(){
    float elapsedTime[30] {}; //init to 0
    uint32_t last_time {time_us_32()};
    while (true){
        uint32_t new_time {time_us_32()};
        uint32_t dt = new_time - last_time;
        last_time = new_time;

        for (PWM_pin* pin : pin_info){
            int pinNumb {pin->pinNumber};
            if (!pinIsInitialized(pinNumb)){
                gpio_init(pinNumb);
                gpio_set_dir(pinNumb, GPIO_OUT);
            }
            elapsedTime[pinNumb] += dt;
            int pinFreq {pin->frequency}; 
            if (elapsedTime[pinNumb] >= pinFreq){
                elapsedTime[pinNumb] -= pinFreq;
                //implement state control and on/off toggle
            }
        }
    }
}