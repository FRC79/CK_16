#include "DriveToFrontAndShoot.h"
#include "../../RobotMap.h"

DriveToFrontAndShoot::DriveToFrontAndShoot(StartingSide side_of_pyr) : CommandGroup("DriveToFrontAndShoot")
{
	switch(side_of_pyr){
		case kLeft:
			// If we chose left.
			break;
		case kRight:
			// If we chose right.
			break;
		default:
			break;
	}
	
//	AddParallel(new SpinShooterWheelsBB(RobotMap::SHOOTER_SPEED)); // Start continuously spinning shooter wheels
//	AddSequential(new DriveDistance(RobotMap::DRIVE_DISTANCE_TO_GOAL, DriveDistance::kForward)); // Drive forward to goal
	AddParallel(new AutoLoad()); // Start continuously autoloading	
//	AddSequential(new FireDisc()); // Fire Disc 1
//	AddSequential(new FireDisc()); // Fire Disc 2
//	AddSequential(new FireDisc()); // Fire Disc 3
//	AddSequential(new StopShooterWheels()); // Stop the shooter wheels
//	AddSequential(new StopAutoLoad()); // Stop the auto loader
}
