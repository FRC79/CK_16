#ifndef TILTPISTON_H
#define TILTPISTON_H

#include "Commands/Subsystem.h"
#include "DoubleSolenoid.h"
#include "../RobotMap.h"

class TiltPiston : public Subsystem
{
public:
	TiltPiston();
	void SetTilt(bool state);
	bool IsTiltedUp();
	void TiltUp();
	void TiltDown();
	void InvertCurrentState();
	
	void InitDefaultCommand();
	
private:
	bool isTiltedUp;
	DoubleSolenoid* tilt;
};

#endif
