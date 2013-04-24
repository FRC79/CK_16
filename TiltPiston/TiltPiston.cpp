#include "TiltPiston.h"

TiltPiston::TiltPiston() : Subsystem("TiltPiston")
{
	isTiltedUp = false;
	tilt = RobotMap::tiltPiston;
}

void TiltPiston::SetTilt(bool state){
	tilt->Set(state ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
	isTiltedUp = state;
}

bool TiltPiston::IsTiltedUp(){
	return isTiltedUp;
}

void TiltPiston::TiltUp(){
	SetTilt(true);
}

void TiltPiston::TiltDown(){
	SetTilt(false);
}

void TiltPiston::InvertCurrentState(){
	SetTilt(!IsTiltedUp());
}

void TiltPiston::InitDefaultCommand()
{
}
