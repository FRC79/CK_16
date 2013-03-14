#ifndef DISCSHOOTER_H
#define DISCSHOOTER_H

#include "Commands/Subsystem.h"
#include "CANJaguar.h"
#include "Solenoid.h"

class DiscShooter : public Subsystem
{
public:
	DiscShooter();
	~DiscShooter();
	void InitDefaultCommand();
	
private:
	CANJaguar *FrontWheel, *BackWheel;
	Solenoid *FirePiston;
};

#endif
