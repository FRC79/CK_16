#include "OperatorArcadeDrive.h"
#include "../../Util/TeleopHelper.h"

OperatorArcadeDrive::OperatorArcadeDrive()
{
	Requires(drive);
	driveJoystick = oi->GetOperatorGamepad1();
}

// Called just before this Command runs the first time
void OperatorArcadeDrive::Initialize(){}

// Called repeatedly when this Command is scheduled to run
void OperatorArcadeDrive::Execute()
{
	// Map joystick to motor output curve
	float powerOut, rotOut;
	powerOut = TeleopHelper::mapJoystickToSpeedOutput(driveJoystick->GetRawAxis(2));
	rotOut = TeleopHelper::mapJoystickToSpeedOutput(driveJoystick->GetRawAxis(1));
	
	drive->ArcadeDrive(powerOut, rotOut);
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorArcadeDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OperatorArcadeDrive::End()
{
	drive->ArcadeDrive(0.0, 0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorArcadeDrive::Interrupted()
{
	drive->ArcadeDrive(0.0, 0.0);
}
