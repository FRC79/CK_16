#include "RollDiscIn.h"

RollDiscIn::RollDiscIn()
{
	RollDiscIn(false);
}

RollDiscIn::RollDiscIn(bool runContinuously)
{
	Requires(rollers);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void RollDiscIn::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void RollDiscIn::Execute()
{
	rollers->Set(RobotMap::ROLLER_POWER);
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RollDiscIn::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void RollDiscIn::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RollDiscIn::Interrupted()
{
	
}
