#include "RunRollersWithBeams.h"

RunRollersWithBeams::RunRollersWithBeams()
{
	Requires(rollers);
}

// Called just before this Command runs the first time
void RunRollersWithBeams::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void RunRollersWithBeams::Execute()
{
	// Roll the rollers until the hopperState is full
    if(!HopperState::IsFull() && !rollers->IsLocked())
    {
        rollers->Set(RobotMap::ROLLER_POWER);
    }
    else
    {
        // When it's full, stop the rollers.
        rollers->Stop();
    }
}

// Make this return true when this Command no longer needs to run execute()
bool RunRollersWithBeams::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RunRollersWithBeams::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunRollersWithBeams::Interrupted()
{
	
}
