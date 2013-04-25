#include "LoadDisc.h"

LoadDisc::LoadDisc()
{
//	Requires(hopper);
}

// Called just before this Command runs the first time
void LoadDisc::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void LoadDisc::Execute()
{
	
	if(hopper->IsDiscReadyToBePunchedDown())
	{
		// If the fire piston isn't locked, punch the next disc into the fire chamber.
		if(!RobotState::load_piston_locked && !hopper->IsDiscInChamber())
		{
			Wait(0.5);
			hopper->FireThenRetractLoadPiston();
			
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool LoadDisc::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LoadDisc::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LoadDisc::Interrupted()
{
	
}
