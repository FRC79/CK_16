#include "OI.h"

OI::OI() {
	// Process operator interface input here.	
	operatorGamepad1 = new Joystick(1);
	operatorGamepad2 = new Joystick(2);
	buttonHelper1 = new ButtonHelper(operatorGamepad1);
	buttonHelper2 = new ButtonHelper(operatorGamepad2);
	fireButton = new JoystickButton(operatorGamepad2, 6);
	autoLoadButton = new JoystickButton(operatorGamepad2, 8);
//	operatorTiltButton = new JoystickButton(operatorGamepad2, 5);
//	driverTiltButton = new JoystickButton(operatorGamepad1, 8);
//	extendHangerButton = new JoystickButton(operatorGamepad1, 6);
}

Joystick* OI::GetOperatorGamepad1()
{
	return operatorGamepad1;
}

Joystick* OI::GetOperatorGamepad2()
{
	return operatorGamepad2;
}

ButtonHelper* OI::GetButtonHelper1()
{
	return buttonHelper1;
}

ButtonHelper* OI::GetButtonHelper2()
{
	return buttonHelper2;
}
