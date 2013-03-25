#include "PointTurn.h"
#include "../RobotMap.h"
#include "../RobotState.h"
#include "Math.h"

/* Constructor used for Goal Alignment. DO NOT USE FOR OTHER PURPOSES. */
PointTurn::PointTurn()
{
	Requires(drive);
	
	motorOut = 0.0;
	special_init = true; // Call for a special Camera Align init.
}

/* Initialize function for Goal Alignment ONLY. */
void PointTurn::GoalAlignmentInit()
{
	// Determine which direction we need to turn and at what angle.
	directionCoeff = RobotState::azimuth / fabs(RobotState::azimuth);
	directionCoeff *= -1.0; // We need to go in the opposite direction of our offset to compensate.
	finalAngle = fabs(RobotState::azimuth);
}

PointTurn::PointTurn(float angle, TurnDirection direction)
{
	Requires(drive);
	
	// Determine which direction we need to turn and at what angle.
	directionCoeff = (float)direction;
	finalAngle = fabs(angle);
	motorOut = 0.0;
	special_init = false; // We aren't using the Camera to align with goal.
}

void PointTurn::RegularInit()
{
	finished_turning = false;
	drive->GetTurnGyro()->Reset(); // Reset gyro to 0.0 heading
}

// Called just before this Command runs the first time
void PointTurn::Initialize()
{
	RegularInit();
	
	if(special_init){
		GoalAlignmentInit();
	}
}

// Called repeatedly when this Command is scheduled to run
void PointTurn::Execute()
{
	// Store the gyro current angle readings (absolute value only).
	double gyroCurrentAngle = fabs(drive->GetTurnGyro()->GetAngle());
	
	// Check to see if we have reached our desired angle.
	if(gyroCurrentAngle < finalAngle)
	{
		// Use P Loop to set our motor output according to how far we are.
		// First, we figure out how far we've turned and inverse the amount
		// since motor output is inversely proportional to degrees already turned.
		motorOut = directionCoeff - (gyroCurrentAngle * directionCoeff / finalAngle);
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
