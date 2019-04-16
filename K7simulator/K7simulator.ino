/*
 Name:		K7simulator.ino
 Created:	4/16/2019 3:43:51 PM
 Author:	Endeavour ESU
*/

#include "JoystickLibrary.h"	// Makes the PC see the Arduino as a games controller
#include <Wire.h>				// I2C bus
#include "MPU6050.h"			// Control the MPU6050
#include "FasLED.h"				// For the status LEDs

// CONSTANTS
//PINs
//PIN_CABLERELEASE
//PIN_AIRBRAKES
//PIN_RUDDER
//PIN_TRIM
//PIN_BUTTON0
//PIN_BUTTON1
//PIN_BUTTON2
//PIN_BUTTON3
//PIN_BUTTON4
//PIN_BUTTON5
//PIN_BUTTON6
//PIN_LED
//Others
//BUTTON_NO 7
//LED_NO 8
//I2C_ADDR_MPU6050

// GLOBAL VARIABLES
//LED oLED[LED_NO];
//Unit8_t iLEDBrightness;
//
//MPU6050 sensor
//Button status
//LEDs
//Potentiometer values
//Reed switch / Hall effect sensor value(cable release)

// INTERRUPT HANDLERS
//Cable release

// the setup function runs once when you press reset or power the board
void setup() {
	//Start the Serial bus
	//Start the I2C bus
	//Initialise the MPU6050 + calibration
	//Setup PINs
	//Initialise button variables
	//Initialise button interrupt(s)
	//Initialise LED
	//Initialise Potentiometers
	//Initialise reed switch / hall effect sensor
	//Initialise joystick library
	//Set ready status LED

}

// the loop function runs over and over again until power down or reset
void loop() {
	// Get MPU6050 axes values
	// Set Joystick axes values
	// Get air brakes value
	// Get rudder value
	// Get trim value
	// Set joystick air brakes value
	// Set joystick rudder value
	// Set joystick trim value
	// Check buttons
	// Set joystick button values
	// Set LED values

}

getPotentiometer(int iPIN, int iMaxValue) {
	Int iValue;

	iValue = analogRead(iPIN); // 0-1023 (10 bits)
	iValue = iValue / (1024 / iMaxValue);
	Return(iValue);
}