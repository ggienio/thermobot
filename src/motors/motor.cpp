#include "Arduino.h"
#include "motor.h"

Motor::Motor(int pin_a, int pin_b) {
    this->pin_a = pin_a;
    this->pin_b = pin_b;
    this->forward();
    this->set_speed(0);
}

void Motor::forward() {
    Serial.println("Forward direction set");
    // TODO: implement
    // set pin_a (or b - check) to a pwm signal with of value this->speed, the other one to LOW
    // use the ledc library
}

void Motor::backward() {
    Serial.println("Backward direction set");
    // TODO: implement
    // opposite of forward
}

void Motor::set_speed(int speed) {
    Serial.println("Speed set");
    // TODO: implement
    // set pwm value of whichever pin is currently used to int speed
}