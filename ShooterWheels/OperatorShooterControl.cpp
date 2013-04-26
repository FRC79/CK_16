#include "OperatorShooterControl.h"
#include "../RobotMap.h"
#include "../Hopper/HopperState.h"
#include "Timer.h"

OperatorShooterControl::OperatorShooterControl()
{
	Requires(CommandBase::shooterWheels);
	
	shooter_power = RobotMap::SHOOTER_POWER;
	wheels_spinning = false;
}

void OperatorShooterControl::Initialize()
{
	// Starting the robot in the same way every time
	wasPressed = false;
}

void OperatorShooterControl::Execute()
{
	// Toggle speeds
	if(CommandBase::oi->GetButtonHelper2()->WasButtonToggled(4))
	{
		if(shooter_power < 0.8){
			shooter_power = 0.8;
		} else {
			shooter_power = 0.6;
		}
	}
	
	// If shooter wheel button is toggled, toggle wheel speed on and off.
	if(CommandBase::oi->GetButtonHelper2()->WasButtonToggled(2)){
		wheels_spinning = !wheels_spinning;
	}
	CommandBase::shooterWheels->SetBothWheels(wheels_spinning ? -shooter_power : 0.0);
	
	// Map fire piston position state to button directly.
	CommandBase::firePiston->Set(CommandBase::oi->GetDriverJoystick()->GetRawButton(6));
	
	if(CommandBase::firePiston->IsExtended())
	{
		CommandBase::loadPiston->SetLocked(true);
	}
	
	if(!wasPressed && CommandBase::oi->GetDriverJoystick()->GetRawButton(6))
	{
		wasPressed = true;
	}
	
	if(wasPressed && !CommandBase::oi->GetDriverJoystick()->GetRawButton(6))
	{
		wasPressed = false;
		Wait(0.5); // Wait for fire piston to come back
		CommandBase::loadPiston->SetLocked(false);
	}
	
	
}

bool OperatorShooterControl::IsFinished()
{
	return false;
}

void OperatorShooterControl::End()
{
	// Stop running the shooter and return to original position
	CommandBase::shooterWheels->Stop();
}

void OperatorShooterControl::Interrupted()
{
	// Stop running the shooter and return to original position
	CommandBase::shooterWheels->Stop();
}
