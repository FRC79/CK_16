#include "DriveToFrontAndShoot.h"

DriveToFrontAndShoot::DriveToFrontAndShoot() : CommandGroup("DriveToFrontAndShoot")
{
	AddParallel(new SpinShooterWheelsBB(3500.0)); // Start continuously spinning shooter wheels
	AddSequential(new DriveDistance(12.0, DriveDistance::kForward)); // Drive 12 in forward
	AddParallel(new AutoLoad()); // Start continuously autoloading	
	// SHOOT (SEQUENTIAL)
	// SHOOT (SEQUENTIAL)
	// SHOOT (SEQUENTIAL)
	AddSequential(new StopShooterWheels());
	// STOP AUTOLOADING (SEQUENTIAL)
}
