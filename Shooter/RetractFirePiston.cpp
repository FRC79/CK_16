#include "RetractFirePiston.h"

RetractFirePiston::RetractFirePiston()
{
	Requires(shooter);
}

// Called just before this Command runs the first time
void RetractFirePiston::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void RetractFirePiston::Execute()
{
	shooter->RetractFirePiston();
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool RetractFirePiston::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void RetractFirePiston::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractFirePiston::Interrupted()
{
	
}
