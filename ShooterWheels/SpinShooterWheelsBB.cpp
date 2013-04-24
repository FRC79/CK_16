#include "SpinShooterWheelsBB.h"

SpinShooterWheelsBB::SpinShooterWheelsBB()
{
	Requires(shooterWheels);
}

// Called just before this Command runs the first time
void SpinShooterWheelsBB::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void SpinShooterWheelsBB::Execute()
{
	isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SpinShooterWheelsBB::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void SpinShooterWheelsBB::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinShooterWheelsBB::Interrupted()
{
	
}
