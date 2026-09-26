#include <stdio.h>
#include <iostream>
#include <random>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "PWM.hpp"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9



int main()
{
    stdio_init_all();

    // // I2C Initialisation. Using it at 400Khz.
    // i2c_init(I2C_PORT, 400*1000);
    
    // gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    // gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    // gpio_pull_up(I2C_SDA);
    // gpio_pull_up(I2C_SCL);
    // // For more examples of I2C use see https://github.com/raspberrypi/pico-examples/tree/master/i2c

    // while (true) {
    //     printf("Hello, world!\n");
    //     sleep_ms(1000);
    // }

    sleep_ms(3000); // wait for serial monitor
    PWM::init();
    
    //random generator
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(0.0, 1.0);
    static std::uniform_real_distribution<double> disHz(27.5, 4186.0);

    // double randomHz {disHz(gen)};
    // std::cout << "random Hz:" << randomHz << std::endl;
    // PWM::pulseAtHz(7, randomHz, 0.1);

    
    while (true){
    //     double randomPercentHz {dis(gen)};
    //     double randomHz {disHz(gen)};
    //     std::cout << "random freq:" << randomPercentHz << std::endl;
    //     std::cout << "random Hz:" << randomHz << std::endl;
    //     PWM::pulseAtHz(7, randomPercentHz, 0.5);
    //     sleep_ms(1000);
    //     PWM::pulseAtHz(7, randomPercentHz, 0.5);
    //     sleep_ms(1000);

        //// HOT CROSS BUNS
        PWM::pulseAtHz(7, PWM::E4);
        sleep_ms(1000);
        PWM::pulseAtHz(7, PWM::D4);
        sleep_ms(1000);
        PWM::pulseAtHz(7, PWM::C4);
        sleep_ms(1600);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(400);

        PWM::pulseAtHz(7, PWM::E4);
        sleep_ms(1000);
        PWM::pulseAtHz(7, PWM::D4);
        sleep_ms(1000);
        PWM::pulseAtHz(7, PWM::C4);
        sleep_ms(1600);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(400);

        PWM::pulseAtHz(7, PWM::C4);
        sleep_ms(400);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(100);
        PWM::pulseAtHz(7, PWM::C4);
        sleep_ms(400);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(100);
        PWM::pulseAtHz(7, PWM::C4);
        sleep_ms(400);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(100);
        PWM::pulseAtHz(7, PWM::C4);
        sleep_ms(400);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(100);

        PWM::pulseAtHz(7, PWM::D4);
        sleep_ms(400);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(100);
        PWM::pulseAtHz(7, PWM::D4);
        sleep_ms(400);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(100);
        PWM::pulseAtHz(7, PWM::D4);
        sleep_ms(400);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(100);
        PWM::pulseAtHz(7, PWM::D4);
        sleep_ms(400);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(100);

        PWM::pulseAtHz(7, PWM::E4);
        sleep_ms(1000);
        PWM::pulseAtHz(7, PWM::D4);
        sleep_ms(1000);
        PWM::pulseAtHz(7, PWM::C4);
        sleep_ms(1600);
        PWM::pulseAtPercentHz(7,0);
        sleep_ms(1400);
    }
    
    return 0;
}
