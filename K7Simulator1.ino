/*
 Name:		K7simulator.ino
 Created:	4/16/2019 3:43:51 PM
 Author:	Endeavour ESU
*/

#include "Wire.h"				// I2C bus
#include "Joystick.h"			// Makes the PC see the Arduino as a games controller
#include "MPU6050_tockn.h"		// Control the MPU6050
#include "FastLED.h"			// For the status LEDs

// CONSTANTS
#define PIN_AIRBRAKE        A0
#define PIN_RUDDER          A1
#define PIN_TRIM            A2

#define PIN_CABLERELEASE    0

#define PIN_SWITCH0         7		// Add height
#define PIN_SWITCH1         8		// Thermal helpers
#define PIN_SWITCH2         9		// Smoke on wings
#define PIN_SWITCH3         10		// Cockpit view
#define PIN_SWITCH4         11		// Pause flight
#define PIN_SWITCH5         12		// Start flight
#define PIN_SWITCH6         13		// Reset

#define	PIN_BUTTON0			7
#define PIN_BUTTON1			8
#define PIN_BUTTON2			9
#define PIN_BUTTON3			10
#define PIN_BUTTON4			11
#define PIN_BUTTON5			12
#define PIN_BUTTON6			13

// PINs
#define PIN_LED				14

// Others
#define BUTTON_NO			7
#define LED_NO				8
#define I2C_ADDR_MPU6050	0x68

// GLOBAL VARIABLES
uint8_t   debug = true;

// Instantiate Joystick library
Joystick_	oJoystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS, 7, 0, true, true, true, false, false, false, true, false, false, true, false);

// MPU6050 sensor
MPU6050		oMPU6050(Wire);

//LED oLED[LED_NO];
uint8_t iLEDBrightness;

// Button status
bool	bButtons[BUTTON_NO];

// LEDs
CRGB	oLEDs[LED_NO];

// Potentiometer values
uint16_t	iRudder,iTrim,iAirBrakes;

// Reed switch / Hall effect sensor value(cable release)
bool			bRelease = false;
unsigned long	iReleaseLastCalled;

// INTERRUPT HANDLERS
// Cable release
// Flip bRelease to true

// the setup function runs once when you press reset or power the board
void setup() {
	//Start the Serial bus
	if (debug == true) {
		Serial.begin(115200);
		Serial.println("K7 simulator starting.");
	}

	// Start the I2C bus
	Wire.begin();

	// Initialise the MPU6050 + calibration
	oMPU6050.begin();
	oMPU6050.calcGyroOffsets(true);

	//Setup PINs
	if (debug == true) {
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

	// Initialise button variables
	int		ButtonState0 = 0;
	int		ButtonState1 = 0;
	int		ButtonState2 = 0;
	int		ButtonState3 = 0;
	int		ButtonState4 = 0;
	int		ButtonState5 = 1;
	int		ButtonState6 = 0;

	bButtons = [FALSE, FALSE, FALS0, FALSE, FALSE, TRUE, FALSE];

	// Initialise button interrupt(s)

	// Initialise LED
	/*
	oLEDs = [0, 0, 0, 0, 0, 1, 0];
	digitalWrite(PIN_LED, HIGH);
	*/
	// Initialise Potentiometers

	// Initialise reed switch / hall effect sensor
	bRelease = digitalRead(PIN_CABLERELEASE);

	//Set ready status LED
	if (debug == true) {
		Serial.println("Setting up Joystick.");
	}

	// Initialise joystick library
	// Set Range Values
	oJoystick.setXAxisRange(-127, 127);
	oJoystick.setYAxisRange(-127, 127);
	oJoystick.setZAxisRange(-127, 127);
	oJoystick.setRudderRange(255, 0);
	oJoystick.begin(true);
}

// the loop function runs over and over again until power down or reset
void loop() {
	// Get MPU6050 axes values
	oMPU6050.update();
	// Set Joystick axes values
	// Calculate x angle as a value from 0 = 1024
	oJoystick.setXAxis(12);
	oJoystick.setYAxis(12);
	oJoystick.setZAxis(12);
	// Get air brakes value
	iAirBrakes = getPotentiomter(PIN_AIRBRAKE, iMaxValue);
	// Get rudder value
	iRudder = getPotentiomter(PIN_RUDDER, iMaxValue);
	// Get trim value
	iTrim = getPotentiomter(PIN_TRIM, iMaxValue);
	// Set joystick air brakes value
	oJoystick.setBrake(12);
	// Set joystick rudder value
	oJoystick.setRudder(12);
	// Set joystick trim value
	// Check buttons

	ButtonState0 = digitalRead(PIN_SWITCH0);
	ButtonState1 = digitalRead(PIN_SWITCH1);
	ButtonState2 = digitalRead(PIN_SWITCH2);
	ButtonState3 = digitalRead(PIN_SWITCH3);
	ButtonState4 = digitalRead(PIN_SWITCH4);
	ButtonState5 = digitalRead(PIN_SWITCH5);
	ButtonState6 = digitalRead(PIN_SWITCH6);

	if ButtonState0 == 0{
		dButton[0] = FALSE;
	}
	else {
		dButton[0] = TRUE;
	}
	if ButtonState1 == 0{
		dButton[1] = FALSE;
	}
	else {
		dButton[1] = TRUE;
	}
	if ButtonState2 == 0{
		dButton[2] = FALSE;
	}
	else {
		dButton[2] = TRUE;
	}
	if ButtonState3 == 0{
		dButton[3] = FALSE;
	}
	else {
		dButton[3] = TRUE;
	}
	if ButtonState4 == 0{
		dButton[4] = FALSE;
	}
	else {
		dButton[4] = TRUE;
	}
	if ButtonState5 == 0{
		dButton[5] = FALSE;
	}
	else {
		dButton[5] = TRUE;
	}
	if ButtonState6 == 0{
		dButton[6] = FALSE;
	}
	else {
		dButton[6] = TRUE;
	}
	// Set joystick button values
	// Set LED values
	delay(25);
}

getPotentiometer(int iPIN, int iMaxValue) {
	int iValue;

	iValue = analogRead(iPIN); // 0-1023 (10 bits)
	iValue = iValue / (1024 / iMaxValue);
	return(iValue);
}