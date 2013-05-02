#ifndef SHOOTERWHEELS_H
#define SHOOTERWHEELS_H

#include "Commands/Subsystem.h"
#include "../Controllers/BangBang_Controller.h"
#include "../RobotMap.h"

class ShooterWheels : public Subsystem
{
public:
	ShooterWheels();

	bool AreWheelsSpinning();
	void SetWheelsSpinning(bool spinning);
	BangBang_Controller* GetFrontBBController();
	BangBang_Controller* GetBackBBController();
	double GetFrontWheelSpeed();
	double GetBackWheelSpeed();
	void SetFrontWheel(float power);
	void SetBackWheel(float power);
	void SetFrontAndBackWheels(float power_front, float power_back);
	void SetBothWheels(float power);
	void Stop();
	
	void InitDefaultCommand();
	
private:
	CANJaguar *frontWheel, *backWheel;
	BangBang_Controller *frontBB, *backBB;
	bool wheelsSpinning;
	float shooter_power;
};

#endif
