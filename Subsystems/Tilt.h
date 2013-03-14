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
	
	bool IsTiltedUp();
	void Set(bool tilted_up);
	void InvertCurrentState();
	void TiltUp();
	void TiltDown();
	
private:
	bool is_tilted_up;
	Solenoid *TiltPiston_In, *TiltPiston_Out;
	DualSolenoid *TiltPiston;
};

#endif
