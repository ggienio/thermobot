#include "movement.h"
#include "Arduino.h"
#include "config.h"

void Movement::move(float vx, float vy, float omega) {
    // Set target velocities
    this->target_vx = vx;
    this->target_vy = vy;
    this->target_omega = omega;
    this->last_move_time = millis();
}

void Movement::update() {
    constexpr float alpha = MovementConf::SMOOTHING_COEFF; 

    // Current speed constantly approaches the target speed
    this->current_vx = (alpha * this->target_vx) + ((1.0 - alpha) * this->current_vx);
    this->current_vy = (alpha * this->target_vy) + ((1.0 - alpha) * this->current_vy);
    this->current_omega = (alpha * this->target_omega) + ((1.0 - alpha) * this->current_omega);

    // --- KINEMATICS (using the SMOOTHED current values) ---
    float speed1 = this->current_vy + this->current_vx + this->current_omega; // M1: Front Left
    float speed2 = this->current_vy - this->current_vx - this->current_omega; // M2: Front Right
    float speed3 = this->current_vy - this->current_vx + this->current_omega; // M3: Rear Left
    float speed4 = this->current_vy + this->current_vx - this->current_omega; // M4: Rear Right

    // --- NORMALIZATION (Movement vector protection) ---
    float max_speed = fmax(fmax(abs(speed1), abs(speed2)), fmax(abs(speed3), abs(speed4)));
    
    if (max_speed > 1.0) {
        speed1 /= max_speed;
        speed2 /= max_speed;
        speed3 /= max_speed;
        speed4 /= max_speed;
    }

    // --- PWM MAPPING ---
    int pwm1 = speed1 * Motors::SPEED_CAP;
    int pwm2 = speed2 * Motors::SPEED_CAP;
    int pwm3 = speed3 * Motors::SPEED_CAP;
    int pwm4 = speed4 * Motors::SPEED_CAP;

    // --- SEND TO MOTORS ---
    m1.set_speed(pwm1);
    m2.set_speed(pwm2);
    m3.set_speed(pwm3);
    m4.set_speed(pwm4);

    stopped = (pwm1 == 0 & pwm2 == 0 & pwm3 == 0 & pwm4 == 0);
    last_update_time = millis();
}

void Movement::loop() {
    unsigned long now = millis();
    if (!stopped && now - last_move_time > MovementConf::TIMEOUT_MS) {
        move(0.0f, 0.0f, 0.0f);
    }
    if (now - last_update_time > MovementConf::UPDATE_PERIOD_MS) {
        update(); 
    }
}