#include "DriveToFrontAndShoot.h"

DriveToFrontAndShoot::DriveToFrontAndShoot() : CommandGroup("DriveToFrontAndShoot")
{
	AddParallel(new SpinShooterWheelsBB(3500.0)); // Start continuously spinning shooter wheels
	AddSequential(new DriveDistance(12.0, DriveDistance::kForward)); // Drive 12 in forward
	AddParallel(new AutoLoad()); // Start continuously autoloading	
	AddSequential(new FireDisc()); // Fire Disc 1
	AddSequential(new FireDisc()); // Fire Disc 2
	AddSequential(new FireDisc()); // Fire Disc 3
	AddSequential(new StopShooterWheels()); // Stop the shooter wheels
	AddSequential(new StopAutoLoad()); // Stop the auto loader
}
