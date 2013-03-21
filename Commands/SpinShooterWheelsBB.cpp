#include "SpinShooterWheelsBB.h"
#include "../Subsystems/DiscShooter.h"
#include "../RobotState.h"

SpinShooterWheelsBB::SpinShooterWheelsBB(float shooter_rpms)
{
	Requires(shooter);
	
	// Init BangBang Controllers for each motor.
	frontSpeed = new BangBang_Controller(shooter->GetShooterWheel(DiscShooter::kFront));
	backSpeed = new BangBang_Controller(shooter->GetShooterWheel(DiscShooter::kBack));
	rpms = shooter_rpms;
}

// Called just before this Command runs the first time
void SpinShooterWheelsBB::Initialize()
{
	// Start the control loops.
	frontSpeed->Set(rpms);
	backSpeed->Set(rpms);
	frontSpeed->Enable();
	backSpeed->Enable();
}

// Called repeatedly when this Command is scheduled to run
void SpinShooterWheelsBB::Execute(){}

// Make this return true when this Command no longer needs to run execute()
bool SpinShooterWheelsBB::IsFinished()
{
	return !RobotState::shooter_wheels_spinning;
}

// Called once after isFinished returns true
void SpinShooterWheelsBB::End()
{
	// Stop the control loop.
	frontSpeed->Disable();
	backSpeed->Disable();
	shooter->StopMotors();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinShooterWheelsBB::Interrupted()
{
	
}
