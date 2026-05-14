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

    // Camera
    constexpr int CAM_PIN_PWDN  = -1;
    constexpr int CAM_PIN_RESET = -1;
    constexpr int CAM_PIN_XCLK  = 15;
    constexpr int CAM_PIN_SIOD  = 4;
    constexpr int CAM_PIN_SIOC  = 5;

    constexpr int CAM_PIN_Y2 = 11;
    constexpr int CAM_PIN_Y3 = 9;
    constexpr int CAM_PIN_Y4 = 8;
    constexpr int CAM_PIN_Y5 = 10;
    constexpr int CAM_PIN_Y6 = 12;
    constexpr int CAM_PIN_Y7 = 18;
    constexpr int CAM_PIN_Y8 = 17;
    constexpr int CAM_PIN_Y9 = 16;

    constexpr int CAM_PIN_VSYNC = 6;
    constexpr int CAM_PIN_HREF  = 7;
    constexpr int CAM_PIN_PCLK  = 13;

    // Servo
    constexpr int SERVO_PIN = 14;
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
    constexpr unsigned long UPDATE_PERIOD_MS = 20; // period with which the motors' speed is updated
    constexpr float SMOOTHING_COEFF = 0.15; // The 'alpha' coefficient determines how fast the robot accelerates (from 0.0 to 1.0).
                                            // 1.0 = instant acceleration (no smoothing).
                                            // 0.15 = smooth, noticeable acceleration over a fraction of a second.
}

#endif // CONFIG_H