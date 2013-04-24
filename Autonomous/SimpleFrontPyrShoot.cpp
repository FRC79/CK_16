#include "SimpleFrontPyrShoot.h"

SimpleFrontPyrShoot::SimpleFrontPyrShoot()
{
}

// Called just before this Command runs the first time
void SimpleFrontPyrShoot::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void SimpleFrontPyrShoot::Execute()
{
	isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SimpleFrontPyrShoot::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void SimpleFrontPyrShoot::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SimpleFrontPyrShoot::Interrupted()
{
	
}
