#include "ReverseRollers.h"

ReverseRollers::ReverseRollers(float power)
{
	Requires(hopper);
	
	roller_power = power;
}

// Called just before this Command runs the first time
void ReverseRollers::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void ReverseRollers::Execute()
{
	hopper->SetRollerMotor(-roller_power);
}

// Make this return true when this Command no longer needs to run execute()
bool ReverseRollers::IsFinished()
{
	return !oi->GetOperatorGamepad2()->GetRawButton(7);
}

// Called once after isFinished returns true
void ReverseRollers::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReverseRollers::Interrupted()
{
	
}
