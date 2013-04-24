#include "LoadPiston.h"
#include "RetractLoadPiston.h"

LoadPiston::LoadPiston() : Subsystem("LoadPiston")
{
	loadPiston = RobotMap::loadPiston;
}

bool LoadPiston::IsLocked(){
	return isLocked;
}

void LoadPiston::SetLocked(bool locked){
	isLocked = locked;
}

bool LoadPiston::IsExtended(){
	return isExtended;
}

void LoadPiston::Set(bool state){
	loadPiston->Set(state);
	isExtended = state;
}

void LoadPiston::Extend(){
	Set(true);
}

void LoadPiston::Retract(){
	Set(false);
}

void LoadPiston::FireThenRetract(){
	Extend();
	Wait(RobotMap::PISTON_DELAY);
	Retract();
	Wait(RobotMap::PISTON_DELAY);
}

void LoadPiston::InvertCurrentState(){
	Set(!IsExtended());
}

void LoadPiston::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new RetractLoadPiston(true));
}
