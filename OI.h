#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "Util/ButtonHelper.h"

class OI {
private:
	Joystick *operatorGamepad1, *operatorGamepad2;
	ButtonHelper *buttonHelper1, *buttonHelper2;
	JoystickButton *autoLoadEnableButton;
	
public:
	OI();
	
	Joystick* GetOperatorGamepad1();
	Joystick* GetOperatorGamepad2();
	ButtonHelper* GetButtonHelper1();
	ButtonHelper* GetButtonHelper2();
};

#endif
