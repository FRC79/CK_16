#include "SpinShooterWheelsBB.h"

SpinShooterWheelsBB::SpinShooterWheelsBB(double front_rpms)
{
	SpinShooterWheelsBB(front_rpms, front_rpms * GEAR_RATIO);
}

SpinShooterWheelsBB::SpinShooterWheelsBB(double front_rpms, double back_rpms)
{
	Requires(shooterWheels);
	frontSpeed = front_rpms;
	backSpeed = back_rpms;
	frontCtrl = shooterWheels->GetFrontBBController();
	backCtrl = shooterWheels->GetBackBBController();
}

// Called just before this Command runs the first time
void SpinShooterWheelsBB::Initialize()
{
	frontCtrl->Set(frontSpeed);
	backCtrl->Set(backSpeed);
	frontCtrl->Enable();
	backCtrl->Enable();
}

// Called repeatedly when this Command is scheduled to run
void SpinShooterWheelsBB::Execute()
{
	frontCtrl->Calculate();
	backCtrl->Calculate();
}

// Make this return true when this Command no longer needs to run execute()
bool SpinShooterWheelsBB::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void SpinShooterWheelsBB::End()
{
	frontCtrl->Disable();
	backCtrl->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpinShooterWheelsBB::Interrupted()
{
	frontCtrl->Disable();
	backCtrl->Disable();
}
