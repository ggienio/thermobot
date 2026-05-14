#include "config.h"
#include "src/motors/motor.h"
#include "src/control/movement.h"
#include "src/comms/comms.h"
#include "src/comms/command_dispatcher.h"
#include "src/camera/camera.h"

static Motor m1(Pins::MOTOR1_PIN_A, Pins::MOTOR1_PIN_B);
static Motor m2(Pins::MOTOR2_PIN_A, Pins::MOTOR2_PIN_B);
static Motor m3(Pins::MOTOR3_PIN_A, Pins::MOTOR3_PIN_B);
static Motor m4(Pins::MOTOR4_PIN_A, Pins::MOTOR4_PIN_B);

static Movement movement(m1, m2, m3, m4);

static CommandDispatcher dispatcher(movement);

static Comms comms(dispatcher);

static Camera cam(
    Pins::CAM_PIN_PWDN,
    Pins::CAM_PIN_RESET,
    Pins::CAM_PIN_XCLK,
    Pins::CAM_PIN_SIOD,
    Pins::CAM_PIN_SIOC,

    Pins::CAM_PIN_Y2,
    Pins::CAM_PIN_Y3,
    Pins::CAM_PIN_Y4,
    Pins::CAM_PIN_Y5,
    Pins::CAM_PIN_Y6,
    Pins::CAM_PIN_Y7,
    Pins::CAM_PIN_Y8,
    Pins::CAM_PIN_Y9,

    Pins::CAM_PIN_VSYNC,
    Pins::CAM_PIN_HREF,
    Pins::CAM_PIN_PCLK
);

void setup() {
    Serial.begin(9600);
    Serial.println("");
    comms.init();
    cam.init();
    delay(1000);
    cam.start_camera_server();
}

void loop() {
    comms.loop();
    movement.loop();
}
