#pragma config(Hubs,  S1, HTMotor,  none,     none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  mtr_S1_C1_1,     motorLeft,     tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorRight,    tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    initializeRobot
//
// Prior to the start of tele-op mode, you may want to perform some initialization on your robot
// and the variables within your program.
//
// In most cases, you may not have to add any code to this function and it will remain "empty".
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeRobot()
{
	// Sensors are automatically configured and setup by ROBOTC. They may need a brief time to stabilize.

	return;
}

const int maxPower = 100;
const short joyStickSize = 256;
const int joyStickDeadzone = 5;

void drive()
{
	short joyY = joystick.joy1_y1 * -1;
	short joyX = joystick.joy1_x2;
    short joyY2 = joystick.joy1_y2;

	if (abs(joyY) < joyStickDeadzone)
		joyY = 0;
	if (abs(joyX) < joyStickDeadzone)
		joyX = 0;
	if (abs(joyY2) < joyStickDeadzone)
		joyY2 = 0;

	float power = maxPower * joyY / (joyStickSize / 2);
	float directionalPercent = joyX / (joyStickSize / 2);
    // The closer to the center, the stronger  the turn strength.
	float directionalStrength = (joyStickSize / 2) / (joyStickSize / 2 + abs(joyY2));

	if (directionalPercent > 0)
	{
		motor[motorLeft] = power - (power * abs(directionalPercent));
		motor[motorRight] = power - motor[motorLeft] * directionalStrength;
	}
	else
	{
		motor[motorRight] = power - (power * abs(directionalPercent));
		motor[motorLeft] = power - motor[motorRight] * directionalStrength;
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                         Main Task
//
// Game controller / joystick information is sent periodically (about every 50 milliseconds) from
// the FMS (Field Management System) to the robot.
//
// At the end of the tele-op period, the FMS will autonmatically abort (stop) execution of the program.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
	initializeRobot();

	// Wait for start of tele-op phase
	waitForStart();

	while (true)
	{
		getJoystickSettings(joystick);
		drive();
	}
}
