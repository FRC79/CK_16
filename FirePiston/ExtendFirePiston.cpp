#include "ExtendFirePiston.h"

ExtendFirePiston::ExtendFirePiston()
{
	ExtendFirePiston(false);
}

ExtendFirePiston::ExtendFirePiston(bool runContinuously) : CommandBase("ExtendFirePiston")
{
	Requires(firePiston);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void ExtendFirePiston::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void ExtendFirePiston::Execute()
{
	if(!firePiston->IsLocked()){
		firePiston->Extend();
		loadPiston->SetLocked(true);
	}
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendFirePiston::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void ExtendFirePiston::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendFirePiston::Interrupted()
{
	
}
