#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "src/motors/motor.h"

class Movement {
private:
    float current_vx;    // current actual velocity in the x direction [-1, 1]
    float current_vy;    // current actual velocity in the y direction [-1, 1]
    float current_omega; // current actual angular velocity [-1, 1]

    float target_vx;     // target velocity requested by the operator [-1, 1]
    float target_vy;     // target velocity requested by the operator [-1, 1]
    float target_omega;  // target angular velocity requested by the operator [-1, 1]
    
    Motor &m1, &m2, &m3, &m4;
    unsigned long last_move_time;
    unsigned long last_update_time;
    bool stopped;

public:
    Movement(Motor &m1, Motor &m2, Motor &m3, Motor &m4):
        current_vx(0), current_vy(0), current_omega(0),
        target_vx(0), target_vy(0), target_omega(0),
        m1(m1), m2(m2), m3(m3), m4(m4),
        last_move_time(0), last_update_time(0), stopped(true) {}

    void move(float vx, float vy, float omega);
    void update();
    void loop();
};

#endif // MOVEMENT_H