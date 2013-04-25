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
	if(!hopper->IsFull()){
		hopper->SetRollerMotor(roller_power);
	} else {
		hopper->StopRollerMotor();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ForwardRollers::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void ForwardRollers::End()
{
	hopper->StopRollerMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ForwardRollers::Interrupted()
{
	hopper->StopRollerMotor();
}
