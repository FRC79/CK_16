#ifndef ROLLERS_H
#define ROLLERS_H

#include "Commands/Subsystem.h"
#include "../RobotMap.h"

class Rollers : public Subsystem
{
public:
	Rollers();

	void Set(float power);
	void Stop();
	
	void InitDefaultCommand();
	
private:
	CANJaguar* roller;
};

#endif
