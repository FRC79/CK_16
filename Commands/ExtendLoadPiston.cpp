#include "ExtendLoadPiston.h"

ExtendLoadPiston::ExtendLoadPiston()
{
	Requires(hopper);
	
	is_finished = false;
}

// Called just before this Command runs the first time
void ExtendLoadPiston::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void ExtendLoadPiston::Execute()
{
	hopper->ExtendLoadPiston();
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendLoadPiston::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void ExtendLoadPiston::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendLoadPiston::Interrupted()
{
	
}
