#include "movement.h"
#include "Arduino.h"
#include "config.h"

void Movement::move(float vx, float vy, float omega) {
    // Calculate base speeds for each wheel (Mecanum Kinematics)
    float speed1 = vy + vx + omega; // M1: Front Left
    float speed2 = vy - vx - omega; // M2: Front Right
    float speed3 = vy - vx + omega; // M3: Rear Left
    float speed4 = vy + vx - omega; // M4: Rear Right

    // Normalization (Movement vector protection)
    // If the summed values of vx, vy, and omega exceed 1.0 (or -1.0), 
    // the motors would receive a command to drive beyond 100% capacity.
    // We must find the maximum value and proportionally scale down all speeds, 
    // so the robot maintains its intended direction.
    float max_speed = fmax(fmax(abs(speed1), abs(speed2)), fmax(abs(speed3), abs(speed4)));

    if (max_speed > 1.0) {
        speed1 /= max_speed;
        speed2 /= max_speed;
        speed3 /= max_speed;
        speed4 /= max_speed;
    }

    // Map values (from -1.0 to 1.0) to PWM signal (from -SPEED_CAP to SPEED_CAP)
    int pwm1 = speed1 * Motors::SPEED_CAP;
    int pwm2 = speed2 * Motors::SPEED_CAP;
    int pwm3 = speed3 * Motors::SPEED_CAP;
    int pwm4 = speed4 * Motors::SPEED_CAP;

    // Send final commands to the physical motors
    m1.set_speed(pwm1);
    m2.set_speed(pwm2);
    m3.set_speed(pwm3);
    m4.set_speed(pwm4);

    // Keep track of whether the robot is stopped and the last move time
    stopped = (vx == 0.0f && vy == 0.0f && omega == 0.0f);
    last_move_time = millis();

    // Serial.println("Movement executed:");
    // Serial.print("    vx: ");
    // Serial.print(vx);
    // Serial.print("    vy: ");
    // Serial.print(vy);
    // Serial.print("    omega: ");
    // Serial.print(omega);
    // Serial.println("");
}

void Movement::update() {
    if (!stopped && millis() - last_move_time > MovementConf::TIMEOUT_MS) {
        move(0.0f, 0.0f, 0.0f);
    }
}