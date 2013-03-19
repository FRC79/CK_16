#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Commands/Subsystem.h"
#include "CANJaguar.h"
#include "Gyro.h"
#include "RobotDrive.h"

class Drivetrain : public Subsystem
{
public:
	Drivetrain();
	~Drivetrain();
	
	typedef enum {kForward = 1, kReverse = -1} Direction;
	
	void InitDefaultCommand();
	
	void ArcadeDrive(float power, float rot);
	void SetLeftAndRightMotorOutputs(float left_power, float right_power);
	void DriveDistance(double distance_in_inches, Direction direction);
	
private:
	CANJaguar *Front_R, *Front_L, *Rear_R, *Rear_L;
	Gyro *TurnGyro;
	RobotDrive *RoboDrive;
};

#endif
