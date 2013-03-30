#include "RunRollerWithBeams.h"

RunRollerWithBeams::RunRollerWithBeams()
{
	Requires(hopper);
	
	roller_power = RobotMap::ROLLER_POWER;
}

// Called just before this Command runs the first time
void RunRollerWithBeams::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void RunRollerWithBeams::Execute()
{
	// Roll the rollers until the hopper is full
	if(!hopper->IsFull())
	{
		hopper->SetRollerMotor(roller_power);
	}
	else
	{
		// When it's full, stop the rollers.
		hopper->StopRollerMotor();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RunRollerWithBeams::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RunRollerWithBeams::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunRollerWithBeams::Interrupted()
{
	
}
