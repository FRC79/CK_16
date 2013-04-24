#include "ArcadeDrive.h"

ArcadeDrive::ArcadeDrive()
{
	Requires(drivetrain);
}

// Called just before this Command runs the first time
void ArcadeDrive::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void ArcadeDrive::Execute()
{
	// Calculate outputs according to drive equation
	double moveOutput, rotOutput;
	moveOutput = TeleopHelper::mapJoystickToPowerOutput(oi->GetDriverJoystick()->GetRawAxis(2));
	rotOutput = TeleopHelper::mapJoystickToPowerOutput(oi->GetDriverJoystick()->GetRawAxis(1));
	
	drivetrain->ArcadeDrive(moveOutput, rotOutput);
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
