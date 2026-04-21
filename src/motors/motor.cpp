#include "Arduino.h"
#include "motor.h"
#include "config.h"

Motor::Motor(int pin_a, int pin_b) {
    this->pin_a = pin_a;
    this->pin_b = pin_b;

    ledcAttach(this->pin_a, Motors::PWM_FREQUENCY, Motors::PWM_RESOLUTION);
    ledcAttach(this->pin_b, Motors::PWM_FREQUENCY, Motors::PWM_RESOLUTION);

    this->set_speed(0);
}

void Motor::set_speed(int speed) {
    // Constrain values exceeding the limit from config.h
    this->speed = constrain(speed, -Motors::SPEED_CAP, Motors::SPEED_CAP);

    // Current control logic for the H-bridge (Cytron MDD3A)
    if (this->speed > 0) {
        // Forward direction - apply PWM to pin A, set pin B to zero
        ledcWrite(this->pin_a, this->speed);
        ledcWrite(this->pin_b, 0);

    } else if (this->speed < 0) {
        // Backward direction - set pin A to zero, apply PWM to pin B
        // ledcWrite only accepts positive numbers
        ledcWrite(this->pin_a, 0);
        ledcWrite(this->pin_b, abs(this->speed));

    } else {
        // Stop (speed 0) - turn off power on both pins
        ledcWrite(this->pin_a, 0);
        ledcWrite(this->pin_b, 0);
    }
}