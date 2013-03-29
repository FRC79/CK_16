#include "ExtendLoadPiston.h"

ExtendLoadPiston::ExtendLoadPiston()
{
	Requires(shooter);
}

// Called just before this Command runs the first time
voidExtendFirePiston::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
voidExtendFirePiston::Execute()
{
	shooter->ExtendLoadPiston();
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
boolExtendFirePiston::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
voidExtendFirePiston::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
voidExtendFirePiston::Interrupted()
{
	
}
