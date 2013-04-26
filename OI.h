#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "Util/ButtonHelper.h"

class OI 
{
public:
	JoystickButton *buttonInvertTiltJoy1, *buttonInvertTiltJoy2,
    	/**buttonInvertHangPiston,*/ *buttonExtendFirePiston, *buttonToggleShooterWheels,
    	*buttonForwardRollers, *buttonReverseRollers, *buttonManualLoadPiston,
    	*buttonToggleAutoLoad, *buttonStopShooterWheels;
	
	OI();
	
	Joystick* GetDriverJoystick();
	Joystick* GetShooterGamepad();
	ButtonHelper* GetButtonHelper1();
	ButtonHelper* GetButtonHelper2();
	
private:
	Joystick *driverJoystick, *shooterGamepad;
	ButtonHelper *buttonHelper1, *buttonHelper2;
};

#endif
