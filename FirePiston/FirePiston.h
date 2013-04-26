#ifndef FIREPISTON_H
#define FIREPISTON_H

#include "Commands/Subsystem.h"
#include "../RobotMap.h"
#include "Solenoid.h"
#include "Timer.h"

class FirePiston : public Subsystem
{
public:
	FirePiston();
	
	void Set(bool state);
	bool IsLocked();
	void SetLocked(bool locked);
	bool IsExtended();
	void Extend();
	void Retract();
	void InvertCurrentState();
	void FireThenRetract();
	
	void InitDefaultCommand();
	
private:
	Solenoid* firePiston;
	bool isExtended;
	bool is_Locked;
};

#endif
