#ifndef HOPPERSTATE_H
#define HOPPERSTATE_H

#include "DigitalInput.h"
#include "../RobotMap.h"

class HopperState
{
public:
	static const UINT8 BROKEN = 0;
	static const UINT8 SOLID = 1;
	
	static void init();
	static bool IsDiscUnderneathRollers();
	static bool IsDiscReadyToLoad();
	static bool IsDiscInChamber();
	static bool IsFull();
	
private:
	static DigitalInput *rollerBeam, *loadBeam, *fireBeam;
};

#endif
