#include "ForwardRollers.h"

ForwardRollers::ForwardRollers(float power)
{
	Requires(hopper);
	
	roller_power = power;
}

// Called just before this Command runs the first time
void ForwardRollers::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void ForwardRollers::Execute()
{
	hopper->SetRollerMotor(roller_power);
}

// Make this return true when this Command no longer needs to run execute()
bool ForwardRollers::IsFinished()
{
	return !oi->GetOperatorGamepad2()->GetRawButton(3);
}

// Called once after isFinished returns true
void ForwardRollers::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ForwardRollers::Interrupted()
{
	
}
