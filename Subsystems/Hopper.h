#ifndef HOPPER_H
#define HOPPER_H

#include "Commands/Subsystem.h"
#include "CANJaguar.h"
#include "Solenoid.h"
#include "DigitalInput.h"

class Hopper : public Subsystem
{ 
public:
	Hopper();
	~Hopper();
	bool IsLoadPistonExtended();
	void SetLoadPiston(bool piston_state);
	void InvertCurrentLoadPistonState();
	void ExtendLoadPiston();
	void RetractLoadPiston();
	void FireThenRetract(double wait_time);
	void InitDefaultCommand();
	bool IsHopperFull();
	bool IsDiscReadyToBePunched();
	bool IsDiscReadyToBeRolledIn(); // These are some long function names but it will pay off in the end -SLC
	
private:
	CANJaguar *Roller; // Speed controller to control rollers
	Solenoid *LoadPiston; // Piston to punch down disc from hopper to shooter
	DigitalInput *LoadBeam, *CheckerBeam; // LoadBeam: Says if we can punch down
										  // CheckerBeam: Checks to see if we need to keep 
										  // rolling for a new disc 
	static const double PISTON_DELAY_TIME = 0.15; // in seconds
	bool Is_Extended;  // Previous States
	static const unsigned int BROKEN = 0;
	static const unsigned int SOLID = 1;
	
};

#endif
