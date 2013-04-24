#include "StopShooterWheels.h"

StopShooterWheels::StopShooterWheels()
{
	StopShooterWheels(false);
}

StopShooterWheels::StopShooterWheels(bool runContinuously)
{
	Requires(shooterWheels);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void StopShooterWheels::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void StopShooterWheels::Execute()
{
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool StopShooterWheels::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void StopShooterWheels::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopShooterWheels::Interrupted()
{
	
}
