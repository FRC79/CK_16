#include "OperatorShooterControl.h"
#include "../../RobotMap.h"

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
