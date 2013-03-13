#ifndef HANGER_H
#define HANGER_H

#include "Commands/Subsystem.h"
#include "../Actuators/DualSolenoid.h"

class Hanger : Subsystem
{
public:
	Hanger();
	~Hanger();
	void InitDefaultCommand();
	
private:
	DualSolenoid *HangPiston_A, *HangPiston_B; // A is in, B is out
};

#endif
