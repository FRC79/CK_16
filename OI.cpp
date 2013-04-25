#include "OI.h"

OI::OI() 
{
	// Init Joystick and Gamepad
	driverJoystick = new Joystick(1);
	shooterGamepad = new Joystick(2);
	buttonHelper1 = new ButtonHelper(driverJoystick);
	buttonHelper2 = new ButtonHelper(shooterGamepad);
	
	// Init Buttons
	buttonInvertTiltJoy1 = new JoystickButton(driverJoystick, 8); // Tilt shooter on joystick
    buttonInvertTiltJoy2 = new JoystickButton(shooterGamepad, 5); // Tilt shooter on gamepad
//    buttonInvertHangPiston = new JoystickButton(driverJoystick, 6); // Invert hang position (timeout needed)
    buttonExtendFirePiston = new JoystickButton(shooterGamepad, 6); // Extend fire piston
    buttonToggleShooterWheels = new JoystickButton(shooterGamepad, 2); // Toggle wheel spinning
    buttonForwardRollers = new JoystickButton(shooterGamepad, 3); // Manually run rollers forward
    buttonReverseRollers = new JoystickButton(shooterGamepad, 7); // Manually run rollers in reverse
    buttonManualLoadPiston = new JoystickButton(shooterGamepad, 1); // Manually control load piston
    buttonToggleAutoLoad = new JoystickButton(shooterGamepad, 8); // Toggle AutoLoad
}

Joystick* OI::GetDriverJoystick()
{
	return driverJoystick;
}

Joystick* OI::GetShooterGamepad()
{
	return shooterGamepad;
}

ButtonHelper* OI::GetButtonHelper1(){
	return buttonHelper1;
}

ButtonHelper* OI::GetButtonHelper2(){
	return buttonHelper2;
}
