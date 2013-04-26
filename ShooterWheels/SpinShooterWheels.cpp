#include "SpinShooterWheels.h"

SpinShooterWheels::SpinShooterWheels()
{
	SpinShooterWheels(false);
}

SpinShooterWheels::SpinShooterWheels(bool runContinuously)
{
	Requires(shooterWheels);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void SpinShooterWheels::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void SpinShooterWheels::Execute()
{
	shooterWheels->SetBothWheels(-RobotMap::SHOOTER_POWER);
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool SpinShooterWheels::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void SpinShooterWheels::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinShooterWheels::Interrupted()
{
	
}
