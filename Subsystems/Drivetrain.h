#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Commands/Subsystem.h"
#include "CANJaguar.h"
#include "Gyro.h"
#include "RobotDrive.h"

class Drivetrain : Subsystem
{
public:
	Drivetrain();
	~Drivetrain();
	
	void InitDefaultCommand();
	
private:
	CANJaguar *FrontR_Wheel, *FrontL_Wheel, *RearR_Wheel, *RearL_Wheel;
	Gyro *TurnGyro;
	RobotDrive *RoboDrive;
};

#endif
