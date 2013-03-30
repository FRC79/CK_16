#include "SetShooterSpeed.h"

SetShooterSpeed::SetShooterSpeed(float speed) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
//	Requires(shooter);
	_speed = speed;
}

// Called just before this Command runs the first time
void SetShooterSpeed::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void SetShooterSpeed::Execute() {
	shooter->SetMotorOutputs(_speed);
}

// Make this return true when this Command no longer needs to run execute()
bool SetShooterSpeed::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SetShooterSpeed::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetShooterSpeed::Interrupted() {
}
