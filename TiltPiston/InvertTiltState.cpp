#include "InvertTiltState.h"

InvertTiltState::InvertTiltState()
{
	InvertTiltState(false);
}

InvertTiltState::InvertTiltState(bool runContinuously) : Command("InvertTiltState")
{
	Requires(tiltPiston);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void InvertTiltState::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void InvertTiltState::Execute()
{
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool InvertTiltState::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void InvertTiltState::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void InvertTiltState::Interrupted()
{
	
}
