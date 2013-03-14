#ifndef HOPPER_H
#define HOPPER_H

#include "Commands/Subsystem.h"
#include "CANJaguar.h"
#include "Solenoid.h"
#include "DigitalInput.h"

class Hopper : Subsystem
{
public:
	Hopper();
	~Hopper();
	
	void InitDefaultCommand();
	
private:
	CANJaguar *Roller; // Speed controller to control rollers
	Solenoid *LoadPiston; // Piston to punch down disc from hopper to shooter
	DigitalInput *LoadBeam, *CheckerBeam; // LoadBeam: Says if we can punch down
										  // CheckerBeam: Checks to see if we need to keep 
										  // rolling for a new disc 
};

#endif
