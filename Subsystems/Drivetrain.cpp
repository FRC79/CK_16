#include "Drivetrain.h"
#include "../RobotMap.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain")
{
	Front_R = new CANJaguar(RobotMap::FRONT_RIGHT_DRIVE_ID);
	Front_L = new CANJaguar(RobotMap::FRONT_LEFT_DRIVE_ID);
	Rear_R = new CANJaguar(RobotMap::REAR_RIGHT_DRIVE_ID);
	Rear_L = new CANJaguar(RobotMap::REAR_LEFT_DRIVE_ID);
	
	RoboDrive = new RobotDrive(Front_R, Front_L, Rear_R, Rear_L);
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

void Drivetrain::InitDefaultCommand()
{
	
}
