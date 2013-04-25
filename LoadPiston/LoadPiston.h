#ifndef LOADPISTON_H
#define LOADPISTON_H

#include "Commands/Subsystem.h"
#include "Solenoid.h"
#include "Timer.h"
#include "../RobotMap.h"

class LoadPiston : public Subsystem
{
public:
	LoadPiston();
	
	bool IsLocked();
	void SetLocked(bool locked);
	bool IsExtended();
	void Set(bool state);
	void Extend();
	void Retract();
	void FireThenRetract();
	void InvertCurrentState();
	
	void InitDefaultCommand();
	
private:
	bool isExtended, isLocked;
	Solenoid* loadPiston;
};

#endif
