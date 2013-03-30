#include "TiltUp.h"

TiltUp::TiltUp()
{
//	Requires(shooter);
}

// Called just before this Command runs the first time
void TiltUp::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void TiltUp::Execute()
{
	shooter->TiltUp();
	RobotState::raised = true;
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool TiltUp::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void TiltUp::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TiltUp::Interrupted()
{
	
}
