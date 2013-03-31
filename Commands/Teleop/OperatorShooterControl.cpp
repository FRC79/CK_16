#include "OperatorShooterControl.h"
#include "../../RobotMap.h"
#include "Timer.h"
#include "../../RobotState.h"

OperatorShooterControl::OperatorShooterControl()
{
	Requires(shooter);
	
	shooter_power = RobotMap::SHOOTER_POWER;
	SmartDashboard::PutNumber("shooter power", shooter_power);
	wheels_spinning = false;
}

void OperatorShooterControl::Initialize()
{
	// Starting the robot in the same way every time
	shooter->StopMotors();
	wasPressed = false;
}

void OperatorShooterControl::Execute()
{
	// Toggle speeds
	if(oi->GetButtonHelper2()->WasButtonToggled(4))
	{
		if(shooter_power < 0.8){
			shooter_power = 0.8;
		} else {
			shooter_power = 0.6;
		}
		SmartDashboard::PutNumber("shooter power", shooter_power);
	}
	
	// If shooter wheel button is toggled, toggle wheel speed on and off.
	if(oi->GetButtonHelper2()->WasButtonToggled(2)){
		wheels_spinning = !wheels_spinning;
	}
	shooter->SetMotorOutputs(wheels_spinning ? -shooter_power : 0.0);
	
	// Map fire piston position state to button directly.
	shooter->SetFirePiston(oi->GetOperatorGamepad2()->GetRawButton(6));
	
	if(shooter->IsFirePistonExtended())
	{
		RobotState::load_piston_locked = true;
	}
	
	if(!wasPressed && oi->GetOperatorGamepad2()->GetRawButton(6))
	{
		wasPressed = true;
	}
	
	if(wasPressed && !oi->GetOperatorGamepad2()->GetRawButton(6))
	{
		wasPressed = false;
		Wait(0.5); // Wait for fire piston to come back
		RobotState::load_piston_locked = false;
	}
	
	
}

bool OperatorShooterControl::IsFinished()
{
	return false;
}

void OperatorShooterControl::End()
{
	// Stop running the shooter and return to original position
	shooter->StopMotors();
}

void OperatorShooterControl::Interrupted()
{
	// Stop running the shooter and return to original position
	shooter->StopMotors();
}
