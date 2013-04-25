#ifndef FIREPISTON_H
#define FIREPISTON_H

#include "Commands/Subsystem.h"
#include "../RobotMap.h"
#include "Timer.h"

class FirePiston : public Subsystem
{
public:
	FirePiston();
	~FirePiston();
	
	void Set(bool state);
	bool IsExtended();
	void Extend();
	void Retract();
	void InvertCurrentState();
	void FireThenRetract();
	
	void InitDefaultCommand();
	
private:
	Solenoid* firePiston;
	bool isExtended;
};

#endif
