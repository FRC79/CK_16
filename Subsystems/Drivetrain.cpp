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

void Drivetrain::SetLeftAndRightMotorOutputs(float left_power, float right_power)
{
	RoboDrive->SetLeftRightMotorOutputs(left_power, right_power); // Left and right sides
}

/* Drives straight until encoder tics are reached. */
void Drivetrain::DriveDistance(double distance_in_inches, Direction direction)
{
	double directionCoeff , revs, tics, motorOut;
	directionCoeff = direction;
	revs = /*distance_in_inches*/ 12.0 / WHEEL_CIRCUMFERENCE;
	tics = revs * TICS_PER_REV;
	motorOut = /*Front_L->GetPosition()*/ 100.0 /* * directionCoeff*/ / tics;
	printf("Motor Ouput: %f\n", motorOut);
//	SetLeftAndRightMotorOutputs(motorOut, motorOut);
}

void Drivetrain::InitDefaultCommand()
{
	
}
