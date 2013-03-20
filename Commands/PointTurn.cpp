#include "PointTurn.h"
#include "../RobotMap.h"
#include "Math.h"

PointTurn::PointTurn(float angle, TurnDirection direction)
{
	Requires(drive);
	
	directionCoeff = (float)direction;
	distInInches = TURN_CIRCUMFERENCE * angle / 360.0;
	revs = distInInches / WHEEL_CIRCUMFERENCE;
	tics = revs * TICS_PER_REV;
	motorOut = 0.0;
}

// Called just before this Command runs the first time
void PointTurn::Initialize()
{
	finished_turning = false;
}

// Called repeatedly when this Command is scheduled to run
void PointTurn::Execute()
{
	// Store the encoder tic readings from the encoders (absolute value only).
	double encoderPos = fabs(drive->GetPosition(Drivetrain::kFrontLeft));
	
	// Check to see if we have turned enough.
	if(encoderPos < tics)
	{
		// Use P Loop to set our motor output according to how far we are.
		motorOut = encoderPos * directionCoeff / tics;
		drive->SetLeftAndRightMotorOutputs(motorOut, -motorOut);
	}
	else
	{
		// Finish the driving task.
		finished_turning = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool PointTurn::IsFinished()
{
	return finished_turning;
}

// Called once after isFinished returns true
void PointTurn::End()
{
	drive->SetMotorOutputs(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PointTurn::Interrupted()
{
	drive->SetMotorOutputs(0.0);
}
