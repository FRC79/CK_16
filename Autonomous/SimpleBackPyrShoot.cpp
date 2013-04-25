#include "SimpleBackPyrShoot.h"

SimpleBackPyrShoot::SimpleBackPyrShoot()
{
	Requires(firePiston);
	Requires(shooterWheels);
	Requires(rollers);
	Requires(loadPiston);
	Requires(hanger);
	Requires(tiltPiston);
}

// Called just before this Command runs the first time
void SimpleBackPyrShoot::Initialize()
{
	tiltPiston->TiltDown();
	hanger->Retract();
	
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void SimpleBackPyrShoot::Execute()
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
    
    // Roll Disc 3 in place
    rollers->Set(RobotMap::ROLLER_POWER);
    Wait(3.0);
    rollers->Stop();
    
    // Load Disc 3
    loadPiston->FireThenRetract();
    
    // Fire Disc 3
    firePiston->FireThenRetract();
    
    // Stop spinning shooter wheels
    shooterWheels->Stop();
	
	isFinished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SimpleBackPyrShoot::IsFinished()
{
	return isFinished;
}

// Called once after isFinished returns true
void SimpleBackPyrShoot::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SimpleBackPyrShoot::Interrupted()
{
	
}
