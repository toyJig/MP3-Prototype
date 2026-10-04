#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <numbers>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/adc.h"

#include "DAC.hpp"

#define SPI_PORT spi0
#define PIN_CS   8
#define PIN_MOSI 7
#define PIN_SCK  6

int main(){
    stdio_init_all();
    spi_init(SPI_PORT, 1e6); // 1MHz SPI
    spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    
    gpio_init(PIN_CS);
    gpio_init(PIN_MOSI);
    gpio_init(PIN_SCK);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_set_dir(PIN_MOSI, GPIO_OUT);
    gpio_set_dir(PIN_SCK, GPIO_OUT);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    
    adc_init();
    adc_gpio_init(26); //Metro RP2040 A0 pin
    adc_select_input(0);

    //wait for serial monitor
    sleep_ms(2000);
    

    double Amplitude {0.6};
    DAC_C DAC1 = DAC_C(SPI_PORT, PIN_CS, PIN_MOSI, PIN_SCK, Amplitude);
    DAC1.init();
    // DAC1.generateAC_Wave(DAC::C4);
    DAC1.generateAC_Wave(1);
}











// int main() {
//     stdio_init_all();
    
//     const uint8_t PIN_PWM_MUSIC = 7;
//     const uint8_t PIN_PWM_VOLUME = 6;
    
//     const uint8_t PIN_BTN_VOL_UP = 3;
//     const uint8_t PIN_BTN_VOL_DOWN = 2;
    
//     sleep_ms(2000); // wait for serial monitor
//     PWM::init();

//     // random generator
//     // static std::random_device rd;
//     // static std::mt19937 gen(rd());
//     // static std::uniform_real_distribution<double> dis(0.0, 1.0);
//     // static std::uniform_real_distribution<double> disHz(27.5, 4186.0);
//     // double randomHz {disHz(gen)};
//     // std::cout << "random Hz:" << randomHz << std::endl;
//     // PWM::pulseAtHz(7, randomHz, 0.1);

//     //button logic
//     gpio_init(PIN_BTN_VOL_UP);
//     gpio_set_dir(PIN_BTN_VOL_UP, GPIO_IN);
//     gpio_pull_up(PIN_BTN_VOL_UP);

//     PWM::pulseAtHz(PIN_PWM_MUSIC, PWM::Bf4, 0.5);
//     PWM::pulseAtHz(PIN_PWM_VOLUME, 20000.0, 0.0);
//     double volume = 0.0;

//     while (true) {
//         if (!gpio_get(PIN_BTN_VOL_UP) && volume < 1.0){
//             volume += 0.05;
//             printf("Button pressed! New volume: %f\n", volume);
//             PWM::changeOnPercent(PIN_PWM_VOLUME, volume);
//         }
//         sleep_ms(100);
//     }
// }


