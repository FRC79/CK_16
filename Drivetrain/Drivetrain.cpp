#include "Drivetrain.h"
#include "StopDriveMotors.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain")
{
	// Init components
	frontL = RobotMap::frontLeftWheel;
	frontR = RobotMap::frontRightWheel;
	rearL = RobotMap::rearLeftWheel;
	rearR = RobotMap::rearRightWheel;
	drive = RobotMap::robotDrive;
}

void Drivetrain::ArcadeDrive(float moveVal, float rotVal){
	drive->ArcadeDrive(moveVal, rotVal);
}

void Drivetrain::SetLeftAndRightMotorOutputs(float left_power, float right_power){
	drive->SetLeftRightMotorOutputs(left_power, right_power);
}

void Drivetrain::Set(float power){
	SetLeftAndRightMotorOutputs(power, power);
}

void Drivetrain::Stop(){
	Set(0.0);
}

void Drivetrain::InitDefaultCommand()
{
	/* We want the drivetrain to stop when we don't send it values to
	 * prevent CAN timeout errors. */
	SetDefaultCommand(new StopDriveMotors(true));
}
