#include "StopDriveMotors.h"

StopDriveMotors::StopDriveMotors()
{
	StopDriveMotors(false);
}

StopDriveMotors::StopDriveMotors(bool runContinuously)
{
	Requires(CommandBase::drivetrain);
	runsForever = runContinuously;
}

// Called just before this Command runs the first time
void StopDriveMotors::Initialize()
{
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void StopDriveMotors::Execute()
{
	// Run this infinitely so that something else has to stop it.
	drivetrain->Stop();
	
	if(!runsForever){
		isFinished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool StopDriveMotors::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void StopDriveMotors::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void StopDriveMotors::Interrupted()
{
	
}
