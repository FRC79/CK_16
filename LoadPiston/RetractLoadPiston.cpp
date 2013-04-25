#include "RetractLoadPiston.h"
#include "../CommandBase.h"

RetractLoadPiston::RetractLoadPiston(){
	RetractLoadPiston(false);
}

RetractLoadPiston::RetractLoadPiston(bool runContinuously){
	Requires(CommandBase::loadPiston);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void RetractLoadPiston::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void RetractLoadPiston::Execute()
{
	CommandBase::loadPiston->Retract();
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool RetractLoadPiston::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void RetractLoadPiston::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractLoadPiston::Interrupted()
{
	
}
