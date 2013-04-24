#include "SimpleBackPyrShoot.h"

SimpleBackPyrShoot::SimpleBackPyrShoot()
{
}

// Called just before this Command runs the first time
void SimpleBackPyrShoot::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void SimpleBackPyrShoot::Execute()
{
	isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SimpleBackPyrShoot::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void SimpleBackPyrShoot::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SimpleBackPyrShoot::Interrupted()
{
	
}
