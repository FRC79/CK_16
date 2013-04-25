#include "RetractFirePiston.h"
#include "../CommandBase.h"

RetractFirePiston::RetractFirePiston()
{
	RetractFirePiston(false);
}

RetractFirePiston::RetractFirePiston(bool runContinuously) : Command("RetractFirePiston")
{
	Requires(CommandBase::firePiston);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void RetractFirePiston::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void RetractFirePiston::Execute()
{
	CommandBase::firePiston->Retract();
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RetractFirePiston::IsFinished()
{
	return isFinished;
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
