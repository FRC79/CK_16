#include "OperatorHopperControl.h"
#include "../../RobotMap.h"

OperatorHopperControl::OperatorHopperControl()
{
	Requires(hopper);
	
	roller_power = RobotMap::ROLLER_POWER;
}

// Called just before this Command runs the first time
void OperatorHopperControl::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void OperatorHopperControl::Execute()
{
	if(oi->GetOperatorGamepad2()->GetRawButton(7))
	{
		// Roll out (reverse) rollers and push out discs.
		hopper->SetRollerMotor(-roller_power);
	}
	else if(oi->GetOperatorGamepad2()->GetRawButton(3) && !hopper->IsFull())
	{
		// Pull in discs until the hopper is full.
		hopper->SetRollerMotor(roller_power);
	}
	else
	{
		// Stop the rollers.
		hopper->StopRollerMotor();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorHopperControl::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OperatorHopperControl::End()
{
	hopper->StopRollerMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorHopperControl::Interrupted()
{
	hopper->StopRollerMotor();
}
