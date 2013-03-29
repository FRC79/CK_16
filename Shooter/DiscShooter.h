#ifndef DISCSHOOTER_H
#define DISCSHOOTER_H

#include "Commands/Subsystem.h"
#include "CANJaguar.h"
#include "Solenoid.h"
#include "../RobotMap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "DoubleSolenoid.h"

class DiscShooter : public Subsystem
{
public:
	
	typedef enum {kFront, kBack} ShooterWheel;
	
	DiscShooter();
	~DiscShooter();
	void InitDefaultCommand();
	
	CANJaguar* GetShooterWheel(ShooterWheel wheel);
	void SetFrontAndBackMotorOutputs(float front_power, float back_power);
	void SetMotorOutputs(float power);
	void StopMotors();

	bool IsFirePistonExtended();
	void SetFirePiston(bool piston_state);
	void InvertCurrentFirePistonState();
	void ExtendFirePiston();
	void RetractFirePiston();
	void FireThenRetract();
	
	bool IsTiltedUp();
	void SetTilt(bool tilted_up);
	void InvertCurrentTiltState();
	void TiltUp();
	void TiltDown();
	
private:
	double piston_delay_time;
	bool is_fire_piston_extended;
	CANJaguar *FrontShooterWheel, *BackShooterWheel;
	Solenoid *FirePiston;
	bool is_tilted_up;
	DoubleSolenoid *TiltPiston;
};

#endif
