#include "FrontPyrShoot.h"
#include "Timer.h"
#include "../../RobotMap.h"

FrontPyrShoot::FrontPyrShoot()
{
	Requires(hopper);
	Requires(shooter);
	Requires(tilt);
	
	shooter_power = RobotMap::SHOOTER_POWER;
	is_finished = false;
}

// Called just before this Command runs the first time
void FrontPyrShoot::Initialize()
{
	tilt->TiltUp();
}

// Called repeatedly when this Command is scheduled to run
void FrontPyrShoot::Execute()
{
	Wait(0.25);
	
	shooter->SetMotorOutputs(shooter_power); // Spin up wheels
	
	Wait(4.0);
	
	shooter->FireThenRetract(); // Fire disc
	
	hopper->FireThenRetractLoadPiston(); // Load disc into chamber
	
	shooter->FireThenRetract(); // Fire disc
	
	shooter->StopMotors(); // Stop wheels
	
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool FrontPyrShoot::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void FrontPyrShoot::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FrontPyrShoot::Interrupted()
{
	
}
