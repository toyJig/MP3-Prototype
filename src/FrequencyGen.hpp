#pragma once
namespace FrequencyGen{
    class Frequency_pin {
        public:
            double power;
            int pinNumber;
            bool onState {false};
            Frequency_pin(int pinNumber, double power);
    };
    
    void pulseAt(int pinNumber, double power);
    
    bool pinIsInitialized(int pinNumber);
    
    void init();
}
