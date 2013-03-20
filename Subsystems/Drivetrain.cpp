#include "Drivetrain.h"
#include "../RobotMap.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain")
{
	Front_R = new CANJaguar(RobotMap::FRONT_RIGHT_DRIVE_ID);
	Front_L = new CANJaguar(RobotMap::FRONT_LEFT_DRIVE_ID);
	Rear_R = new CANJaguar(RobotMap::REAR_RIGHT_DRIVE_ID);
	Rear_L = new CANJaguar(RobotMap::REAR_LEFT_DRIVE_ID);
	
	RoboDrive = new RobotDrive(Front_R, Front_L, Rear_R, Rear_L);
	TurnGyro = new Gyro(RobotMap::TURN_GYRO_ID);
}

Drivetrain::~Drivetrain()
{
	delete Front_R;
	delete Front_L;
	delete Rear_R;
	delete Rear_L;
}

void Drivetrain::ArcadeDrive(float power, float rot)
{
	RoboDrive->ArcadeDrive(power, rot, false); // Power and rotation
}

Gyro* Drivetrain::GetTurnGyro()
{
	return TurnGyro;
}

void Drivetrain::SetLeftAndRightMotorOutputs(float left_power, float right_power)
{
	RoboDrive->SetLeftRightMotorOutputs(left_power, right_power); // Left and right sides
}

void Drivetrain::SetMotorOutputs(float power)
{
	SetLeftAndRightMotorOutputs(power, power);
}

/* Get encoder value for the specified motor */
double Drivetrain::GetPosition(Motor encoder_motor)
{
	switch(encoder_motor){
	case kFrontRight:
		return Front_R->GetPosition();
		break;
	case kFrontLeft:
		return Front_L->GetPosition();
		break;
	case kRearRight:
		return Rear_R->GetPosition();
		break;
	case kRearLeft:
		return Rear_L->GetPosition();
		break;
	default:
		return 0.0;
		break;
	}
}

void Drivetrain::InitDefaultCommand()
{
	
}
