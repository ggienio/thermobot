#ifndef CONFIG_H
#define CONFIG_H

namespace Pins {
    // Motors
    // 
    // M1---M2
    //  |   |
    // M3---M4
    //
    constexpr int MOTOR1_PIN_A = 1;
    constexpr int MOTOR1_PIN_B = 2;
    
    constexpr int MOTOR2_PIN_A = 42;
    constexpr int MOTOR2_PIN_B = 41;
    
    constexpr int MOTOR3_PIN_A = 40;
    constexpr int MOTOR3_PIN_B = 39;

    constexpr int MOTOR4_PIN_A = 47;
    constexpr int MOTOR4_PIN_B = 21;
}

namespace WiFiConf {
    constexpr const char* AP_SSID = "THERMOBOT";
    constexpr const char* AP_PASSWORD = "thermobot32";
}

namespace Motors {
    constexpr int PWM_RESOLUTION = 12; // 12 bit resolution: 0 - 4095
    constexpr int PWM_FREQUENCY = 5000;
    constexpr int SPEED_CAP = 2047; // should not exceed 65% as the motors are rated for 9V, driver 3A continuous
}

namespace MovementConf {
    constexpr unsigned long TIMEOUT_MS = 500; // timeout after which to shut down the motor if no command received
}

#endif // CONFIG_H