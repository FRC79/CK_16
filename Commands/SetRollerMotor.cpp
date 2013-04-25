#include "SetRollerMotor.h"

SetRollerMotor::SetRollerMotor(float power)
{
	Requires(hopper);
	
	roller_power = power;
}

// Called just before this Command runs the first time
void SetRollerMotor::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void SetRollerMotor::Execute()
{
	hopper->SetRollerMotor(roller_power);
}

// Make this return true when this Command no longer needs to run execute()
bool SetRollerMotor::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void SetRollerMotor::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetRollerMotor::Interrupted()
{
	
}
