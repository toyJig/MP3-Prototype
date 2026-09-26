#pragma once
namespace PWM{
    class PWM_pin {
        public:
            double Hz;
            double onPercent {0.5};
            int pinNumber;
            bool onState {false};
            PWM_pin(int pinNumber, double Hz, double onPercent);
            PWM_pin(int pinNumber, double Hz);
    };

    // inline constexpr double C4 {2616.3};
    // inline constexpr double Cs4 {2771.8};
    // inline constexpr double Df4 {2771.8};
    // inline constexpr double D4 {2936.6};
    // inline constexpr double Ds4 {3111.3};
    // inline constexpr double Ef4 {3111.3};
    // inline constexpr double E4 {3296.3};
    // inline constexpr double F4 {3492.3};
    // inline constexpr double Fs4 {3700.0};
    // inline constexpr double Gf4 {3700.0};
    // inline constexpr double G4 {3920.0};
    // inline constexpr double Gs4 {4153.0};
    // inline constexpr double Af4 {4153.0};
    // inline constexpr double A4 {4400.0};
    // inline constexpr double As4 {4661.6};
    // inline constexpr double Bf4 {4661.6};
    // inline constexpr double B4 {4938.8};
    // inline constexpr double C5 {5232.5};

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

    double percentHzToHz(double Hz);
    
    void pulseAtHz(int pinNumber, double Hz, double onPercent = 0.5);
    void pulseAtPercentHz(int pinNumber, double percentOfMaxHz, double onPercent = 0.5);
    
    bool pinIsInitialized(int pinNumber);
    
    void init();
}
