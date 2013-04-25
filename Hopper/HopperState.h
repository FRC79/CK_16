#ifndef HOPPERSTATE_H
#define HOPPERSTATE_H

#include "DigitalInput.h"
#include "../RobotMap.h"

class HopperState
{
public:
	static const UINT8 BROKEN = 0;
	static const UINT8 SOLID = 1;
	
	HopperState();
	bool IsDiscUnderneathRollers();
	bool IsDiscReadyToLoad();
	bool IsDiscInChamber();
	bool IsFull();
	
private:
	DigitalInput *rollerBeam, *loadBeam, *fireBeam;
};

#endif
