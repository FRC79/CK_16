#include "AlignWithGoal.h"

AlignWithGoal::AlignWithGoal() : CommandGroup("AlignWithGoal")
{
	AddSequential(new FindGoal()); // Query the SmartDashboard for Vision Tracking results.
	AddSequential(new PointTurn()); // Point turns to the desired angle to compensate for our offset.
}
