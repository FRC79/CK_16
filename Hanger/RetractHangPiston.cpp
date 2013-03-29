#include "RetractHangPiston.h"

RetractHangPiston::RetractHangPiston()
{
	Requires(hanger);
}

// Called just before this Command runs the first time
void RetractHangPiston::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void RetractHangPiston::Execute()
{
	hanger->Retract();
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool RetractHangPiston::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void RetractHangPiston::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractHangPiston::Interrupted()
{
	
}
