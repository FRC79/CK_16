#include "TiltDown.h"

TiltDown::TiltDown()
{
	Requires(shooter);
}

// Called just before this Command runs the first time
void TiltDown::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void TiltDown::Execute()
{
	shooter->TiltDown();
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool TiltDown::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void TiltDown::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TiltDown::Interrupted()
{
	
}
