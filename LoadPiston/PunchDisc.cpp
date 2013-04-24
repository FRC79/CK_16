#include "PunchDisc.h"

PunchDisc::PunchDisc()
{
}

// Called just before this Command runs the first time
void PunchDisc::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void PunchDisc::Execute()
{
	isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool PunchDisc::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void PunchDisc::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PunchDisc::Interrupted()
{
	
}
