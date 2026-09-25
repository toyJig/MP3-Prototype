#pragma once
namespace PWM{
    class PWM_pin {
        public:
            int power;
            int pinNumber;
            bool onState {false};
            PWM_pin(int pinNumber, int power);
    };
    
    void pulseAt(int pinNumber, double power);
    
    bool pinIsInitialized(int pinNumber);
    
    void init();
}
