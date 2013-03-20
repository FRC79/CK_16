#include "DriveDistance.h"
#include "../RobotMap.h"
#include "Math.h"

DriveDistance::DriveDistance(double distance_in_inches, Direction direction)
{
	Requires(drive);
	
	directionCoeff = (float)direction;
	revs = fabs(distance_in_inches) / WHEEL_CIRCUMFERENCE;
	tics = revs * TICS_PER_REV;
	motorOut = 0.0;
}

// Called just before this Command runs the first time
void DriveDistance::Initialize()
{
	finished_driving = false;
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute()
{
	// Store the encoder tic readings from the encoders (absolute value only).
	double encoderPos = fabs(drive->GetPosition(Drivetrain::kFrontLeft));
	
	// Check to see if we have reached our destination.
	if(encoderPos < tics)
	{
		// Use P Loop to set our motor output according to how far we are.
		// For this, we find out how far we have driven and feed the inverse value to
		// the motors because velocity is inversely proportional to the distance driven.
		motorOut = directionCoeff - (encoderPos * directionCoeff / tics);
		drive->SetMotorOutputs(motorOut);
	}
	else
	{
		// Finish the driving task.
		finished_driving = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished()
{
	return finished_driving;
}

// Called once after isFinished returns true
void DriveDistance::End()
{
	drive->SetMotorOutputs(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted()
{
	drive->SetMotorOutputs(0.0);
}
