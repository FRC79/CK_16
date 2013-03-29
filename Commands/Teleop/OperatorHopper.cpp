#include "OperatorHopper.h"

OperatorHopper::OperatorHopper()
{
	autoLoad = new AutoLoad();
}

// Called just before this Command runs the first time
void OperatorHopper::Initialize()
{
	autoLoad->Start();
	auto_loading = true;
}

// Called repeatedly when this Command is scheduled to run
void OperatorHopper::Execute()
{
	// Toggle autoload
	if(oi->GetButtonHelper2()->WasButtonToggled(8))
	{
		if(auto_loading) // If we are auto loading, stop autoloading.
		{
			autoLoad->Cancel();
			auto_loading = false;
		}
		else // If not, start auto loading
		{
			autoLoad->Start();
			auto_loading = true;
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool OperatorHopper::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void OperatorHopper::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OperatorHopper::Interrupted()
{
	
}
