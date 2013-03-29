#include "RetractLoadPiston.h"

RetractLoadPiston::RetractLoadPiston()
{
	Requires(hopper);
	
	is_finished = false;
}

// Called just before this Command runs the first time
void RetractLoadPiston::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void RetractLoadPiston::Execute()
{
	hopper->RetractLoadPiston();
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool RetractLoadPiston::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void RetractLoadPiston::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractLoadPiston::Interrupted()
{
	
}
