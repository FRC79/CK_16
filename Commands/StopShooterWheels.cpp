#include "StopShooterWheels.h"
#include "../RobotState.h"

StopShooterWheels::StopShooterWheels(){}

// Called just before this Command runs the first time
void StopShooterWheels::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void StopShooterWheels::Execute()
{
	// Stop shooter wheels from spinning.
	RobotState::shooter_wheels_spinning = false;
	
	// Finish command.
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool StopShooterWheels::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void StopShooterWheels::End(){}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopShooterWheels::Interrupted(){}
