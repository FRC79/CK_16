#ifndef DRIVETOFRONTANDSHOOT_H
#define DRIVETOFRONTANDSHOOT_H

#include "Commands/CommandGroup.h"

#include "../AutoLoad.h"
#include "../DriveDistance.h"
#include "../SpinShooterWheelsBB.h"
#include "../StopShooterWheels.h"

class DriveToFrontAndShoot : public CommandGroup
{
public:
	DriveToFrontAndShoot();
};

#endif
