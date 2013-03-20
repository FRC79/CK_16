#include "DriveToFrontAndShoot.h"

DriveToFrontAndShoot::DriveToFrontAndShoot() : CommandGroup("DriveToFrontAndShoot")
{
	AddSequential(new DriveDistance(12.0, DriveDistance::kForward)); // Drive 12 in forward
}
