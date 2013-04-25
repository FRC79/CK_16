#include "AutoLoad.h"

AutoLoad::AutoLoad() : CommandGroup("AutoLoad")
{
	AddParallel(new RunRollerWithBeams());
	AddParallel(new LoadDisc());
}
