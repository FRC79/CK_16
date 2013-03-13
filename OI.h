#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
	Joystick* operatorGamepad1;
	Joystick* operatorGamepad2;
	
public:
	OI();
	
	Joystick* GetOperatorGamepad1();
	Joystick* GetOperatorGamepad2();
};

#endif
