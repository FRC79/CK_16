#include "OperatorToggleTilt.h"

OperatorToggleTilt::OperatorToggleTilt()
{
	Requires(tilt);
}

// Called just before this Command runs the first time
void OperatorToggleTilt::Initialize(){}

// Called repeatedly when this Command is scheduled to run
void OperatorToggleTilt::Execute()
{
	// If either user toggles the tilt button, the tilt piston changes 
	// to the opposite position.
	if(oi->GetButtonHelper1()->WasButtonToggled(5) ||
			oi->GetButtonHelper2()->WasButtonToggled(5))
	{
		tilt->InvertCurrentState();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorToggleTilt::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OperatorToggleTilt::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorToggleTilt::Interrupted()
{
	
}
