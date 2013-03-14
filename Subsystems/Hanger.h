#ifndef HANGER_H
#define HANGER_H

#include "Commands/Subsystem.h"
#include "../Actuators/DualSolenoid.h"

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
	Solenoid *HangPiston_A_In, *HangPiston_A_Out;
	Solenoid *HangPiston_B_In, *HangPiston_B_Out;
	DualSolenoid *HangPiston_A, *HangPiston_B; // A is in, B is out
};

#endif
