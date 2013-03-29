#include "BackPyrShoot.h"
#include "Timer.h"
#include "../../RobotMap.h"

BackPyrShoot::BackPyrShoot()
{
	Requires(hopper);
	Requires(shooter);
	Requires(tilt);
	Requires(hanger);
	
	shooter_power = RobotMap::SHOOTER_POWER;
	roller_power = RobotMap::ROLLER_POWER;
	is_finished = false;
}

void BackPyrShoot::Initialize()
{
	hanger->Retract();
	tilt->TiltDown();
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void BackPyrShoot::Execute()
{
	Wait(0.25);
		
	shooter->SetMotorOutputs(-shooter_power); // Spin up wheels
	
	Wait(4.0);
	
	shooter->FireThenRetract(); // Fire disc
	
	hopper->FireThenRetractLoadPiston(); // Load disc into chamber
	
	shooter->FireThenRetract(); // Fire disc
	
	hopper->SetRollerMotor(roller_power);
	
	Wait(1.0);
	
	hopper->StopRollerMotor();
	
	hopper->FireThenRetractLoadPiston(); // Load disc into chamber
		
	shooter->FireThenRetract(); // Fire disc	
	
	shooter->StopMotors(); // Stop wheels
	
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool BackPyrShoot::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void BackPyrShoot::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BackPyrShoot::Interrupted()
{
	
}
