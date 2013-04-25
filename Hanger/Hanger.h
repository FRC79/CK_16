#ifndef HANGER_H
#define HANGER_H

#include "Commands/Subsystem.h"
#include "DoubleSolenoid.h"
#include "../RobotMap.h"

class Hanger : public Subsystem
{
public:
	Hanger();
	void Set(bool state);
	bool IsExtended();
	void Extend();
	void Retract();
	void InvertCurrentState();
	
	void InitDefaultCommand();
	
private:
	bool is_Extended;
	DoubleSolenoid *hangA, *hangB;
};

#endif
