#include "InvertWheelState.h"

InvertWheelState::InvertWheelState()
{
	Requires(shooterWheels);
}

// Called just before this Command runs the first time
void InvertWheelState::Initialize()
{
	shooterWheels->SetWheelsSpinning(!shooterWheels->AreWheelsSpinning());
}

// Called repeatedly when this Command is scheduled to run
void InvertWheelState::Execute()
{
}

// Make this return true when this Command no longer needs to run execute()
bool InvertWheelState::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void InvertWheelState::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void InvertWheelState::Interrupted()
{
	
}
