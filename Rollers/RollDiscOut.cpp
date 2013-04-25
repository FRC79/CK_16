#include "RollDiscOut.h"

RollDiscOut::RollDiscOut()
{
	RollDiscOut(false);
}

RollDiscOut::RollDiscOut(bool runContinuously)
{
	Requires(rollers);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void RollDiscOut::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void RollDiscOut::Execute()
{
	rollers->Set(-RobotMap::ROLLER_POWER);
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RollDiscOut::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void RollDiscOut::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RollDiscOut::Interrupted()
{
	
}
