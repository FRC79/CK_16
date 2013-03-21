#include "AutoLoad.h"
#include "Timer.h"
#include "../RobotState.h"

AutoLoad::AutoLoad()
{
	Requires(hopper);
}

// Called just before this Command runs the first time
void AutoLoad::Initialize()
{
	RobotState::auto_load_piston_locked = false;
	RobotState::auto_loading = true;
}

// Called repeatedly when this Command is scheduled to run
void AutoLoad::Execute()
{
	// Roll the rollers until the hopper is full
	if(!hopper->IsFull())
	{
		hopper->SetRollerMotor(0.5);
	}
	else
	{
		// When it's full, stop the rollers.
		hopper->StopRollerMotor();
		
		// If the fire piston isn't locked, punch the next disc into the fire chamber.
		if(!RobotState::auto_load_piston_locked)
		{
			hopper->FireThenRetractLoadPiston();
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AutoLoad::IsFinished()
{
	return !RobotState::auto_loading;
}

// Called once after isFinished returns true
void AutoLoad::End()
{
	hopper->SetRollerMotor(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoLoad::Interrupted()
{
	hopper->SetRollerMotor(0.0);
}
