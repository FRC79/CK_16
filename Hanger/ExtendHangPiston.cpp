#include "ExtendHangPiston.h"

ExtendHangPiston::ExtendHangPiston()
{
	Requires(hanger);

}

// Called just before this Command runs the first time
void ExtendHangPiston::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void ExtendHangPiston::Execute()
{
	hanger->Extend();
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool ExtendHangPiston::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void ExtendHangPiston::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ExtendHangPiston::Interrupted()
{
	
}
