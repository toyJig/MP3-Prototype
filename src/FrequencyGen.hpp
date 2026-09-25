#pragma once
namespace FrequencyGen{
    class Frequency_pin {
        public:
            double power;
            int pinNumber;
            bool onState {false};
            Frequency_pin(int pinNumber, double power);
    };

    inline constexpr double C4 {261.63};
    inline constexpr double Cs4 {277.18};
    inline constexpr double Df4 {277.18};
    inline constexpr double D4 {293.66};
    inline constexpr double Ds4 {311.13};
    inline constexpr double Ef4 {311.13};
    inline constexpr double E4 {329.63};
    inline constexpr double F4 {349.23};
    inline constexpr double Fs4 {370.00};
    inline constexpr double Gf4 {370.00};
    inline constexpr double G4 {392.00};
    inline constexpr double Gs4 {415.30};
    inline constexpr double Af4 {415.30};
    inline constexpr double A4 {440.00};
    inline constexpr double As4 {466.16};
    inline constexpr double Bf4 {466.16};
    inline constexpr double B4 {493.88};
    inline constexpr double C5 {523.25};

    double powerToHz(double power);
    double HzToPower(double Hz);
    
    void pulseAtPercentPower(int pinNumber, double power);
    void pulseAtHz(int pinNumber, double Hz);
    
    bool pinIsInitialized(int pinNumber);
    
    void init();
}
