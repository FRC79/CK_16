#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Commands/Subsystem.h"
#include "CANJaguar.h"
#include "RobotDrive.h"
#include "../RobotMap.h"

class Drivetrain : public Subsystem
{
public:
	Drivetrain();
	
	void ArcadeDrive(float moveVal, float rotVal);
	
	void SetLeftAndRightMotorOutputs(float powerLeft, float powerRight);
	void Set(float power);
	void Stop();
	
	void InitDefaultCommand();
	
private:
	CANJaguar *frontL, *frontR, *rearL, *rearR;
	RobotDrive *drive;
};

#endif
