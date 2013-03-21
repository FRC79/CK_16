#include "FireDisc.h"
#include "Timer.h"
#include "../RobotState.h"

FireDisc::FireDisc()
{
	Requires(shooter);
	
	startDelay = 0.0;
}

FireDisc::FireDisc(double start_delay)
{
	Requires(shooter);
	
	startDelay = start_delay;
}

// Called just before this Command runs the first time
void FireDisc::Initialize()
{
	is_finished = false;
	RobotState::auto_load_piston_locked = true;
}

// Called repeatedly when this Command is scheduled to run
void FireDisc::Execute()
{
	// Wait the specified amount of time to start
	Wait(startDelay);
	
	// Only fire the disc if the wheels are spinning
	if(RobotState::shooter_wheels_spinning)
	{
		shooter->FireThenRetract();
	}

	// Finish the task.
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool FireDisc::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void FireDisc::End()
{
	RobotState::auto_load_piston_locked = false;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FireDisc::Interrupted()
{
	
}
