#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <numbers>
#include "hardware/spi.h"
#include "pico/stdlib.h"
// #include "hardware/adc.h"

#include "DAC.hpp"

#define SPI_PORT spi0
#define PIN_CS   8
#define PIN_MOSI 7
#define PIN_SCK  6

int main() {
    stdio_init_all();
    spi_init(SPI_PORT, 2e6);  // 2MHz SPI
    spi_set_format(SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_init(PIN_CS);
    gpio_init(PIN_MOSI);
    gpio_init(PIN_SCK);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_set_dir(PIN_MOSI, GPIO_OUT);
    gpio_set_dir(PIN_SCK, GPIO_OUT);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    // Metro RP2040 A0 pin for debugging
    // adc_init();
    // adc_gpio_init(26);  
    // adc_select_input(0);

    // wait for serial monitor
    sleep_ms(2000);


    double Amplitude{ 0.25 };
    DAC_C DAC1 = DAC_C(SPI_PORT, PIN_CS, PIN_MOSI, PIN_SCK, Amplitude);
    DAC1.init();
    DAC1.generateAC_Wave(DAC::C4);
}