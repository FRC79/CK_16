#include "FirePiston.h"
#include "RetractFirePiston.h"

FirePiston::FirePiston() : Subsystem("FirePiston")
{
	firePiston = RobotMap::firePiston;
	isExtended = false;
}

bool FirePiston::IsLocked(){
	return is_Locked;
}

void FirePiston::SetLocked(bool locked){
	is_Locked = locked;
}

void FirePiston::Set(bool state){
	firePiston->Set(state);
	isExtended = state;
}

bool FirePiston::IsExtended(){
	return isExtended;
}
void FirePiston::Extend(){
	Set(true);
}
void FirePiston::Retract(){
	Set(false);
}
void FirePiston::InvertCurrentState(){
	Set(!IsExtended());
}
void FirePiston::FireThenRetract(){
	Extend();
	Wait(RobotMap::PISTON_DELAY);
	Retract();
	Wait(RobotMap::PISTON_DELAY);
}

void FirePiston::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new RetractFirePiston(true));
}
