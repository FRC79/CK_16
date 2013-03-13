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
	CANJaguar *Front_R, *Front_L, *Rear_R, *Rear_L;
	Gyro *TurnGyro;
	RobotDrive *RoboDrive;
};

#endif
