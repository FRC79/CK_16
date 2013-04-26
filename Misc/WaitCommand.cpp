#include "WaitCommand.h"

WaitC::WaitC(double timeInSeconds){
	SetTimeout(timeInSeconds);
}

WaitC::WaitC(double timeInSeconds, Subsystem *s){
	Requires(s);
	SetTimeout(timeInSeconds);
	SetInterruptible(false);
}

// Called just before this Command runs the first time
void WaitC::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void WaitC::Execute()
{
	printf("WAITING\n");
}

// Make this return true when this Command no longer needs to run execute()
bool WaitC::IsFinished()
{
	return IsTimedOut(); // WaitCommand for time to expire to finish task.
}

// Called once after isFinished returns true
void WaitC::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitC::Interrupted()
{
	
}
