#include "FrontPyrShoot.h"
#include "Timer.h"

FrontPyrShoot::FrontPyrShoot()
{
	Requires(hopper);
	Requires(shooter);
	Requires(tilt);
	
	shooter_power = -0.6;
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
	
	shooter->FireThenRetract(1.0); // Fire disc
	
	Wait(1.0); // wait for piston to retract
	
	hopper->FireThenRetractLoadPiston(1.0); // Load disc into chamber
	
	Wait(1.0); // wait for piston to retract
	
	shooter->FireThenRetract(1.0); // Fire disc
	
	Wait(1.0); // wait for piston to retract
	
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
