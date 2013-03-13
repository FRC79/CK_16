#include "OI.h"

OI::OI() {
	// Process operator interface input here.
	
	operatorGamepad1 = new Joystick(1);
	operatorGamepad2 = new Joystick(2);
}

Joystick* OI::GetOperatorGamepad1()
{
	return operatorGamepad1;
}

Joystick* OI::GetOperatorGamepad2()
{
	return operatorGamepad2;
}
