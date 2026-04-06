#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
    int pin_a;
    int pin_b;
    int speed;

public:
    Motor(int pin_a, int pin_b);
    void set_speed(int speed);  // [-Motors::PWM_RESOLUTION, Motors::PWM_RESOLUTION]
};

#endif // MOTOR_H