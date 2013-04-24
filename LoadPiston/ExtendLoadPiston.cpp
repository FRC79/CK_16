#include "ExtendLoadPiston.h"

ExtendLoadPiston::ExtendLoadPiston()
{
	ExtendLoadPiston(false);
}

ExtendLoadPiston::ExtendLoadPiston(bool runContinuously)
{
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void ExtendLoadPiston::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void ExtendLoadPiston::Execute()
{
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendLoadPiston::IsFinished()
{
	return isFinished;
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
