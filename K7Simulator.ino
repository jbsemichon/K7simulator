#include <Wire.h>
#include <Joystick.h>
// NEED TO INCLUDE MPU-6050

#define   PIN_AIRBRAKE        A0
#define   PIN_RUDDER          A1
#define   PIN_TRIM            A2

#define   PIN_CABLERELEASE    0
#define   PIN_SWITCH0         7
#define   PIN_SWITCH1         8
#define   PIN_SWITCH2         9
#define   PIN_SWITCH3         10
#define   PIN_SWITCH4         11
#define   PIN_SWITCH5         12
#define   PIN_SWITCH6         13

#define   MPU6050_ADDRESS     0x68

uint8_t   debug = true;

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK, 7, 0,
          true, true, true, false, false, false, true, false, false, true, false);

void setup() {
  // put your setup code here, to run once:
  if (debug == true) {
    Serial.begin(38400);
    Serial.println("K7 simulator starting.");
    Serial.println("Setting PINs.");
  }
  pinMode(PIN_AIRBRAKE, INPUT);
  pinMode(PIN_RUDDER, INPUT);
  pinMode(PIN_TRIM, INPUT);

  pinMode(PIN_CABLERELEASE, INPUT_PULLUP);
  pinMode(PIN_SWITCH0, INPUT_PULLUP);
  pinMode(PIN_SWITCH1, INPUT_PULLUP);
  pinMode(PIN_SWITCH2, INPUT_PULLUP);
  pinMode(PIN_SWITCH3, INPUT_PULLUP);
  pinMode(PIN_SWITCH4, INPUT_PULLUP);
  pinMode(PIN_SWITCH5, INPUT_PULLUP);
  pinMode(PIN_SWITCH6, INPUT_PULLUP);

  if (debug == true) {
    Serial.println("Setting up Joystick.");
  }
  Joystick.begin(true);

  // Setup MPU-6050
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(500);
  Serial.println("Hello");

  // Read from MPU and set Joystick
  Joystick.setXAxis(512);
  Joystick.setYAxis(512);
  Joystick.setZAxis(512);
  Joystick.setRudder(512);
  Joystick.setBrake(512);
  
  delay(10);
}
