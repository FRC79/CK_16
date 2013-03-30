#include "FireDisc.h"

FireDisc::FireDisc() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(shooter);
}

// Called just before this Command runs the first time
void FireDisc::Initialize() {
	isFinished = false;
}

// Called repeatedly when this Command is scheduled to run
void FireDisc::Execute() {
	if(RobotState::shooter_wheels_spinning)
	{
		RobotState::load_piston_locked = true;
		shooter->ExtendFirePiston();
		Wait(0.5);
		shooter->RetractFirePiston();
		Wait(0.125);
		RobotState::load_piston_locked = false;
	}
	isFinished = true;
	
}

// Make this return true when this Command no longer needs to run execute()
bool FireDisc::IsFinished() {
	return isFinished;
}

// Called once after isFinished returns true
void FireDisc::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FireDisc::Interrupted() {
}
