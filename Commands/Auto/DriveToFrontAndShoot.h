#ifndef DRIVETOFRONTANDSHOOT_H
#define DRIVETOFRONTANDSHOOT_H

#include "Commands/CommandGroup.h"

#include "../AutoLoad.h"
#include "../DriveDistance.h"
#include "../SpinShooterWheelsBB.h"
#include "../FireDisc.h"
#include "../StopShooterWheels.h"
#include "../StopAutoLoad.h"

class DriveToFrontAndShoot : public CommandGroup
{
public:
	
	typedef enum {kLeft, kRight} StartingSide;
	
	DriveToFrontAndShoot(StartingSide side_of_pyr);
};

#endif