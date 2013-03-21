#include "StopAutoLoad.h"
#include "../RobotState.h"

StopAutoLoad::StopAutoLoad(){}

// Called just before this Command runs the first time
void StopAutoLoad::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void StopAutoLoad::Execute()
{
	// Stop the auto loader.
	RobotState::auto_loading = false;
	
	// Finish the task.
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool StopAutoLoad::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void StopAutoLoad::End(){}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopAutoLoad::Interrupted(){}
