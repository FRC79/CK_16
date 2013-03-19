#include "TestDrive.h"

TestDrive::TestDrive()
{
	Requires(drive);
}

// Called just before this Command runs the first time
void TestDrive::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void TestDrive::Execute()
{
	drive->DriveDistance(12.0, Drivetrain::kForward);
}

// Make this return true when this Command no longer needs to run execute()
bool TestDrive::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void TestDrive::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestDrive::Interrupted()
{
	
}
