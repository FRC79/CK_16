
#ifndef SHOOTER_H
#define SHOOTER_H 

#include "Timer.h"
#include "DiscAutoLoader.h"
#include "CANJaguar.h"
#include "Solenoid.h"


#define SHOOTER_DELAY 0.25

class Shooter
{
public:
	Shooter(CANJaguar* rear, CANJaguar* front, Solenoid *fireCyinder, DiscAutoLoader *loader);
	~Shooter();
	void Enable();
	void Disable();
	void EnableAutomaticFire();
	void DisableAutomaticFire();
	void Fire();
	void StopFire()

private:
	Task *m_task;
	bool auto_fire;
	CANJaguar *m_rear, *m_front;
	DiscAutoLoader *m_loader; // Ok, this is only here so I have access to the isLoaded property
	bool m_fire;
	bool m_enable;
	Solenoid m_fireCylinder;

};


#endif