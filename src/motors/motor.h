#ifndef MOTOR_H
#define MOTOR_H

class Motor {
private:
    int pin_a;
    int pin_b;
    int speed;

public:
    Motor(int pin_a, int pin_b);
    void set_speed(int speed);  // 0 to Motors::PWM_RESOLUTION
    void forward();
    void backward();
};

#endif // MOTOR_H