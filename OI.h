#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI 
{
public:
	JoystickButton *buttonInvertTiltJoy1, *buttonInvertTiltJoy2,
    	*buttonInvertHangPiston, *buttonExtendFirePiston, *buttonToggleShooterWheels,
    	*buttonForwardRollers, *buttonReverseRollers, *buttonManualLoadPiston,
    	*buttonToggleAutoLoad;
	
	OI();
	
	Joystick* GetDriverJoystick();
	Joystick* GetShooterGamepad();
	
private:
	Joystick *driverJoystick, *shooterGamepad;
};

#endif
