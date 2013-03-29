#include "ArcadeDrive.h"

ArcadeDrive::ArcadeDrive()
{
	Requires(drive);
}

// Called just before this Command runs the first time
void ArcadeDrive::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void ArcadeDrive::Execute()
{
	// Map joystick to motor output curve
	float powerOut, rotOut;
	powerOut = TeleopHelper::mapJoystickToSpeedOutput(oi->operatorGamepad1->GetRawAxis(2));
	rotOut = TeleopHelper::mapJoystickToSpeedOutput(oi->operatorGamepad1->GetRawAxis(1));
	
	drive->ArcadeDrive(powerOut, rotOut);
}

// Make this return true when this Command no longer needs to run execute()
bool ArcadeDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ArcadeDrive::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArcadeDrive::Interrupted()
{
	
}
