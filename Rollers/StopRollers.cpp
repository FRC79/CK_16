#include "StopRollers.h"
#include "../CommandBase.h"

StopRollers::StopRollers()
{
	StopRollers(false);
}

StopRollers::StopRollers(bool runContinuously) : Command("StopRollers")
{
	Requires(CommandBase::rollers);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void StopRollers::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void StopRollers::Execute()
{
	CommandBase::rollers->Stop();
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool StopRollers::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void StopRollers::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopRollers::Interrupted()
{
	
}
