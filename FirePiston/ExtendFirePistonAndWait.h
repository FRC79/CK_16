#ifndef EXTENDFIREPISTONANDWAIT_H
#define EXTENDFIREPISTONANDWAIT_H

#include "Commands/CommandGroup.h"
#include "../CommandBase.h"
#include "../FirePiston/ExtendFirePiston.h"
#include "../RobotMap.h"
#include "../Misc/WaitCommand.h"

class ExtendFirePistonAndWait : public CommandGroup
{
public:
	ExtendFirePistonAndWait();
};

#endif
