#include "ExtendFirePistonAndWait.h"

ExtendFirePistonAndWait::ExtendFirePistonAndWait() : CommandGroup("ExtendFirePistonAndWait")
{
	AddSequential(new ExtendFirePiston(true));
	AddSequential(new WaitC(RobotMap::FIRE_PISTON_DELAY, CommandBase::firePiston));
}
