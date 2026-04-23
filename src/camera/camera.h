#ifndef CAMERA_H
#define CAMERA_H

class Camera {
private:
    int pin_pwdn;
    int pin_reset;
    int pin_xclk;
    int pin_siod;
    int pin_sioc;

    int pin_y2;
    int pin_y3;
    int pin_y4;
    int pin_y5;
    int pin_y6;
    int pin_y7;
    int pin_y8;
    int pin_y9;

    int pin_vsync;
    int pin_href;
    int pin_pclk;

public:
    Camera(
        int pin_pwdn,
        int pin_reset,
        int pin_xclk,
        int pin_siod,
        int pin_sioc,

        int pin_y2,
        int pin_y3,
        int pin_y4,
        int pin_y5,
        int pin_y6,
        int pin_y7,
        int pin_y8,
        int pin_y9,

        int pin_vsync,
        int pin_href,
        int pin_pclk
    ): 
        pin_pwdn(pin_pwdn),
        pin_reset(pin_reset),
        pin_xclk(pin_xclk),
        pin_siod(pin_siod),
        pin_sioc(pin_sioc),

        pin_y2(pin_y2),
        pin_y3(pin_y3),
        pin_y4(pin_y4),
        pin_y5(pin_y5),
        pin_y6(pin_y6),
        pin_y7(pin_y7),
        pin_y8(pin_y8),
        pin_y9(pin_y9),

        pin_vsync(pin_vsync),
        pin_href(pin_href),
        pin_pclk(pin_pclk) {};

    void init();
    void start_camera_server();
};

#endif // CAMERA_H