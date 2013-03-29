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
	
	typedef enum {kFrontRight, kFrontLeft, kRearRight, kRearLeft} Motor;
	
	void InitDefaultCommand();
	
	void ArcadeDrive(float power, float rot);
	
	Gyro* GetTurnGyro();
	void SetLeftAndRightMotorOutputs(float left_power, float right_power);
	void SetMotorOutputs(float power);
	double GetPosition(Motor encoder_motor);
	
private:
	CANJaguar *Front_R, *Front_L, *Rear_R, *Rear_L;
	Gyro *TurnGyro;
	RobotDrive *RoboDrive;
};

#endif
