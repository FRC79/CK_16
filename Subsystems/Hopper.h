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
	
	void SetRollerMotor(float power);
	void StopRollerMotor();
	
	bool IsLoadPistonExtended();
	void SetLoadPiston(bool piston_state);
	void InvertCurrentLoadPistonState();
	void ExtendLoadPiston();
	void RetractLoadPiston();
	void FireThenRetractLoadPiston();
	
	bool IsDiscReadyToBePunchedDown();
	bool IsDiscUnderneathRollers(); // These are some long function names but it will pay off in the end -SLC
	bool IsFull();
	void InitDefaultCommand();
	
private:
	CANJaguar *Roller; // Speed controller to control rollers
	Solenoid *LoadPiston; // Piston to punch down disc from hopper to shooter
	DigitalInput *LoadBeam, *RollerBeam; // LoadBeam: Says if we can punch down
										  // RollerBeam: Checks to see if we need to keep 
										  // rolling for a new disc 
	static const double PISTON_DELAY_TIME = 0.15; // in seconds
	bool is_extended;  // Previous States
	static const unsigned int BROKEN = 0;
	static const unsigned int SOLID = 1;
};

#endif
