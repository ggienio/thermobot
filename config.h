#ifndef CONFIG_H
#define CONFIG_H

namespace Pins {
    // Motors
    // 
    // M1---M2
    //  |   |
    // M3---M4
    //
    constexpr int MOTOR1_PIN_A = 0;
    constexpr int MOTOR1_PIN_B = 0;
    
    constexpr int MOTOR2_PIN_A = 0;
    constexpr int MOTOR2_PIN_B = 0;
    
    constexpr int MOTOR3_PIN_A = 0;
    constexpr int MOTOR3_PIN_B = 0;

    constexpr int MOTOR4_PIN_A = 0;
    constexpr int MOTOR4_PIN_B = 0;
}

namespace WiFiConf {
    constexpr const char* AP_SSID = "THERMOBOT";
    constexpr const char* AP_PASSWORD = "thermobot32";
}

namespace Motors {
    constexpr int PWM_RESOLUTION = 12; // 12 bit resolution: 0 - 4095
    constexpr int SPEED_CAP = 4095;
}

namespace MovementConf {
    constexpr unsigned long TIMEOUT_MS = 500; // timeout after which to shut down the motor if no command received
}

#endif // CONFIG_H