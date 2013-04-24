#include "CancelCommand.h"

CancelCommand::CancelCommand(Command *command)
{
	commandToCancel = command;
}

// Called just before this Command runs the first time
void CancelCommand::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void CancelCommand::Execute()
{
	commandToCancel->Cancel();
	isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool CancelCommand::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void CancelCommand::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CancelCommand::Interrupted()
{
	
}
