#include "PunchDisc.h"

PunchDisc::PunchDisc()
{
	Requires(loadPiston);
}

// Called just before this Command runs the first time
void PunchDisc::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void PunchDisc::Execute()
{
	if(hopperState->IsDiscReadyToLoad())
	{
		/* If the fire piston isn't locked, punch the next disc into 
		 * the fire chamber. */
		if(!loadPiston->IsLocked() && !hopperState->IsDiscInChamber())
		{
			// Wait for disc to transfer completely to punch zone.
			Wait(RobotMap::ROLLER_TO_PUNCH_ZONE_DELAY);
			
			loadPiston->FireThenRetract(); // Open, wait, close, wait
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool PunchDisc::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void PunchDisc::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PunchDisc::Interrupted()
{
	
}
