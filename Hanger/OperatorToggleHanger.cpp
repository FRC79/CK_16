#include "OperatorToggleHanger.h"

OperatorToggleHanger::OperatorToggleHanger()
{
	Requires(CommandBase::hanger);
}

// Called just before this Command runs the first time
void OperatorToggleHanger::Initialize(){}

// Called repeatedly when this Command is scheduled to run
void OperatorToggleHanger::Execute()
{
	// If the user toggled the hang button, the hang pistons change
	// to the opposite position.
	if(CommandBase::oi->GetButtonHelper1()->WasButtonToggled(6))
	{
		CommandBase::hanger->InvertCurrentState();
		printf("HANG CHANGED\n");
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorToggleHanger::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OperatorToggleHanger::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorToggleHanger::Interrupted()
{
	
}
