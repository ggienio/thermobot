#include "config.h"
#include "src/motors/motor.h"
#include "src/control/movement.h"
#include "src/comms/comms.h"
#include "src/comms/command_dispatcher.h"

static Motor m1(Pins::MOTOR1_PIN_A, Pins::MOTOR1_PIN_B);
static Motor m2(Pins::MOTOR2_PIN_A, Pins::MOTOR2_PIN_B);
static Motor m3(Pins::MOTOR3_PIN_A, Pins::MOTOR3_PIN_B);
static Motor m4(Pins::MOTOR4_PIN_A, Pins::MOTOR4_PIN_B);

static Movement movement(m1, m2, m3, m4);

static CommandDispatcher dispatcher(movement);

static Comms comms(dispatcher);

void setup() {
  Serial.begin(9600);
  comms.init();
}

void loop() {
  comms.loop();
  movement.update();
  delay(1000);
}
