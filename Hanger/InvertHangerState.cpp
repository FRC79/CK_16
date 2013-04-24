#include "InvertHangerState.h"

InvertHangerState::InvertHangerState()
{
	Requires(hanger);
	SetTimeout(RobotMap::PISTON_DELAY); // Wait time to finish task.
}

// Called just before this Command runs the first time
void InvertHangerState::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void InvertHangerState::Execute()
{
	hanger->InvertCurrentState();
	
	if(!isFinished){
		hanger->InvertCurrentState();
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool InvertHangerState::IsFinished()
{
	return IsTimedOut(); // Wait for the timeout in order to end the task.
}

// Called once after isFinished returns true
void InvertHangerState::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void InvertHangerState::Interrupted()
{
	
}
