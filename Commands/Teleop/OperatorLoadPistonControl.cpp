#include "OperatorLoadPistonControl.h"
#include "SmartDashboard/SmartDashboard.h"
#include "../../RobotMap.h"
#include "../../RobotState.h"

OperatorLoadPistonControl::OperatorLoadPistonControl()
{
//	Requires(hopper);
	
	roller_power = RobotMap::ROLLER_POWER;
}

// Called just before this Command runs the first time
void OperatorLoadPistonControl::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void OperatorLoadPistonControl::Execute()
{	
	if(!RobotState::auto_loading)
	{
		// Directly map load piston to joystick
		hopper->SetLoadPiston(oi->GetOperatorGamepad2()->GetRawButton(1));
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorLoadPistonControl::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OperatorLoadPistonControl::End()
{
	hopper->StopRollerMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorLoadPistonControl::Interrupted()
{
	hopper->StopRollerMotor();
}
