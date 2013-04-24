#include "RunRollersWithBeams.h"

RunRollersWithBeams::RunRollersWithBeams()
{
}

// Called just before this Command runs the first time
void RunRollersWithBeams::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void RunRollersWithBeams::Execute()
{
	isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool RunRollersWithBeams::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void RunRollersWithBeams::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunRollersWithBeams::Interrupted()
{
	
}
