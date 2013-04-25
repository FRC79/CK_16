#include "ShooterWheels.h"
#include "StopShooterWheels.h"

ShooterWheels::ShooterWheels() : Subsystem("ShooterWheels")
{
	frontWheel = RobotMap::shooterFrontWheel;
	backWheel = RobotMap::shooterBackWheel;
	frontBB = new BangBang_Controller(frontWheel);
	backBB = new BangBang_Controller(backWheel);
}

BangBang_Controller* ShooterWheels::GetFrontBBController(){
	return frontBB;
}

BangBang_Controller* ShooterWheels::GetBackBBController(){
	return backBB;
}

double ShooterWheels::GetFrontWheelSpeed(){
	return frontWheel->GetSpeed();
}

double ShooterWheels::GetBackWheelSpeed(){
	return backWheel->GetSpeed();
}

void ShooterWheels::SetFrontWheel(float power){
	frontWheel->Set(power);
}

void ShooterWheels::SetBackWheel(float power){
	backWheel->Set(power);
}

void ShooterWheels::SetFrontAndBackWheels(float power_front, float power_back){
	SetFrontWheel(power_front);
	SetBackWheel(power_back);
}

void ShooterWheels::SetBothWheels(float power){
	SetFrontAndBackWheels(power, power);
}

void ShooterWheels::Stop(){
	SetBothWheels(0.0);
}

void ShooterWheels::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new StopShooterWheels(true));
}
