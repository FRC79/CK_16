#ifndef HANGER_H
#define HANGER_H

#include "Commands/Subsystem.h"
#include "DoubleSolenoid.h"

class Hanger : public Subsystem
{
public:
	Hanger();
	~Hanger();
	void InitDefaultCommand();
	
	bool IsHangerExtended();
	void Set(bool extend_state);
	void InverseCurrentState();
	void Extend();
	void Retract();
	
private:
	bool is_extended;
	DoubleSolenoid *HangPiston_A, *HangPiston_B; // A is in, B is out
};

#endif
