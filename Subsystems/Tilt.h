#ifndef TILT_H
#define TILT_H

#include "Commands/Subsystem.h"
#include "../Actuators/DualSolenoid.h"

class Tilt : public Subsystem
{
public:
	Tilt();
	~Tilt();
	
	void InitDefaultCommand();
	
private:
	DualSolenoid *TiltPiston;
};

#endif
