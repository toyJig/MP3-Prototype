#include <stdio.h>
#include <iostream>
#include <random>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "FrequencyGen.hpp"

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
    FrequencyGen::init();
    
    //random generator
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(0.0, 1.0);
    static std::uniform_real_distribution<double> disHz(27.5, 4186.0);

    
    while (true){
        double randomFreq {dis(gen)};
        double randomHz {disHz(gen)};
        std::cout << "random freq:" << randomFreq << std::endl;
        std::cout << "random Hz:" << randomHz << std::endl;
        FrequencyGen::pulseAtHz(7, FrequencyGen::E4);
        sleep_ms(1000);
        FrequencyGen::pulseAtHz(7, FrequencyGen::D4);
        sleep_ms(1000);
        FrequencyGen::pulseAtHz(7, FrequencyGen::C4);
        sleep_ms(1600);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(400);

        FrequencyGen::pulseAtHz(7, FrequencyGen::E4);
        sleep_ms(1000);
        FrequencyGen::pulseAtHz(7, FrequencyGen::D4);
        sleep_ms(1000);
        FrequencyGen::pulseAtHz(7, FrequencyGen::C4);
        sleep_ms(1600);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(400);

        FrequencyGen::pulseAtHz(7, FrequencyGen::C4);
        sleep_ms(400);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(100);
        FrequencyGen::pulseAtHz(7, FrequencyGen::C4);
        sleep_ms(400);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(100);
        FrequencyGen::pulseAtHz(7, FrequencyGen::C4);
        sleep_ms(400);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(100);
        FrequencyGen::pulseAtHz(7, FrequencyGen::C4);
        sleep_ms(400);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(100);

        FrequencyGen::pulseAtHz(7, FrequencyGen::D4);
        sleep_ms(400);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(100);
        FrequencyGen::pulseAtHz(7, FrequencyGen::D4);
        sleep_ms(400);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(100);
        FrequencyGen::pulseAtHz(7, FrequencyGen::D4);
        sleep_ms(400);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(100);
        FrequencyGen::pulseAtHz(7, FrequencyGen::D4);
        sleep_ms(400);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(100);

        FrequencyGen::pulseAtHz(7, FrequencyGen::E4);
        sleep_ms(1000);
        FrequencyGen::pulseAtHz(7, FrequencyGen::D4);
        sleep_ms(1000);
        FrequencyGen::pulseAtHz(7, FrequencyGen::C4);
        sleep_ms(1600);
        FrequencyGen::pulseAtPercentPower(7,0);
        sleep_ms(1400);
    }
    
    return 0;
}
