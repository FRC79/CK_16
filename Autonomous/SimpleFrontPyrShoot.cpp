#include "SimpleFrontPyrShoot.h"

SimpleFrontPyrShoot::SimpleFrontPyrShoot()
{
	Requires(firePiston);
	Requires(shooterWheels);
	Requires(rollers);
	Requires(loadPiston);
	Requires(hanger);
	Requires(tiltPiston);
}

// Called just before this Command runs the first time
void SimpleFrontPyrShoot::Initialize()
{
	tiltPiston->TiltUp();
	hanger->Extend();
	
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void SimpleFrontPyrShoot::Execute()
{
	Wait(0.1);
		        
    // Spin up wheels and wait for them to spin up.
    shooterWheels->SetBothWheels(-RobotMap::SHOOTER_POWER);
    Wait(4.0);
    
    // Fire Disc 1
    firePiston->FireThenRetract();
    
    // Load Disc 2
    loadPiston->FireThenRetract();
    
    // Fire Disc 2
    firePiston->FireThenRetract();
    
    // Stop spinning shooter wheels
    shooterWheels->Stop();
	
	isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SimpleFrontPyrShoot::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void SimpleFrontPyrShoot::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SimpleFrontPyrShoot::Interrupted()
{
	
}
