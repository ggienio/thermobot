#include "movement.h"
#include "Arduino.h"
#include "config.h"

void Movement::move(float vx, float vy, float omega) {
    // TODO: implement
    // convert vx, vy and omega [-1, 1] to the range accepted by pwm [-Motors:SPEED_CAP, Motors::SPEED_CAP]
    // call appropriate methods of each motor so that they move in the desired way
    
    stopped = (vx == 0.0f && vy == 0.0f && omega == 0.0f);
    last_move_time = millis();

    Serial.println("Movement executed:");
    Serial.print("    vx: ");
    Serial.print(vx);
    Serial.print("    vy: ");
    Serial.print(vy);
    Serial.print("    omega: ");
    Serial.print(omega);
    Serial.println("");
}

void Movement::update() {
    if (!stopped && millis() - last_move_time > MovementConf::TIMEOUT_MS) {
        move(0.0f, 0.0f, 0.0f);
    }
}