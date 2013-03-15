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
	
	void SetFrontAndBackMotorOutputs(float front_power, float back_power);
	void SetMotorOutputs(float power);
	void StopMotors();
	bool IsFirePistonExtended();
	void SetFirePiston(bool piston_state);
	void InvertCurrentFirePistonState();
	void ExtendFirePiston();
	void RetractFirePiston();
	void FireThenRetract(double wait_time);
	
private:
	static const double PISTON_DELAY_TIME = 0.15; // in seconds
	bool is_fire_piston_extended;
	CANJaguar *FrontShooterWheel, *BackShooterWheel;
	Solenoid *FirePiston;
};

#endif
