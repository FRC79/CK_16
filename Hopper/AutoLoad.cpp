#include "AutoLoad.h"

AutoLoad::AutoLoad() : CommandGroup("AutoLoad")
{
	AddParallel(new PunchDisc());
	AddParallel(new RunRollersWithBeams());
}
