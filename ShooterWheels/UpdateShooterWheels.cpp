#include "UpdateShooterWheels.h"

UpdateShooterWheels::UpdateShooterWheels()
{
	UpdateShooterWheels(false);
}

UpdateShooterWheels::UpdateShooterWheels(bool runContinuously)
{
	Requires(CommandBase::shooterWheels);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void UpdateShooterWheels::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void UpdateShooterWheels::Execute()
{
	if(CommandBase::shooterWheels->AreWheelsSpinning()){
		CommandBase::shooterWheels->SetBothWheels(-RobotMap::SHOOTER_POWER);
	} else {
		CommandBase::shooterWheels->Stop();
	}
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool UpdateShooterWheels::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void UpdateShooterWheels::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UpdateShooterWheels::Interrupted()
{
	
}
