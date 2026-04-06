#include "Arduino.h"
#include "motor.h"
#include "config.h"

Motor::Motor(int pin_a, int pin_b) {
    this->pin_a = pin_a;
    this->pin_b = pin_b;
    this->set_speed(0);
}

void Motor::set_speed(int speed) {
    Serial.println("Speed set");
    this->speed = constrain(speed, -Motors::SPEED_CAP, Motors::SPEED_CAP);
    // TODO: implement
    // set pin_a (or b - if speed < 0) to a pwm signal of value this->speed, the other one to 0
    // use the ledc library
}