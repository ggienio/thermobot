#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "src/motors/motor.h"

class Movement {
private:
    float vx;    // velocity in the x direction [-1, 1]
    float vy;    // velocity in the y direction [-1, 1]
    float omega; // angular velocity [-1, 1]
    
    Motor &m1, &m2, &m3, &m4;

public:
    Movement(Motor &m1, Motor &m2, Motor &m3, Motor &m4):
        vx(0), vy(0), omega(0), m1(m1), m2(m2), m3(m3), m4(m4) {};

    void move(float vx, float vy, float omega);
};

#endif // MOVEMENT_H