#include "Hopper.h"
#include "../RobotMap.h"
#include "Timer.h"

// Constructor: where we construct things (initialization)
Hopper::Hopper() : Subsystem("Hopper")
{
	Roller = new CANJaguar(RobotMap::ROLLER_MOTOR_ID);
	LoadPiston = new Solenoid(RobotMap::HOPPER_LOAD_PISTON_ID);
	LoadBeam = new DigitalInput(RobotMap::LOAD_BEAM_SENSOR_ID);
	CheckerBeam = new DigitalInput(RobotMap::CHECKER_BEAM_SENSOR_ID);
	
	Is_Extended = false; // Prevent explosions
}

Hopper::~Hopper()
{
	delete Roller;
	delete LoadPiston;
	delete LoadBeam;
	delete CheckerBeam;
}

bool Hopper::IsLoadPistonExtended() {
	return Is_Extended;
}

void Hopper::SetLoadPiston(bool piston_state) {
	LoadPiston->Set(piston_state);
	Is_Extended = piston_state;
}

void Hopper::InvertCurrentLoadPistonState() {
	SetLoadPiston(!IsLoadPistonExtended());
}

void Hopper::ExtendLoadPiston() {
	SetLoadPiston(true);
}

void Hopper::RetractLoadPiston() {
	SetLoadPiston(false);
}

/* Extends and then retracts the load piston after a 
 * certain period of time. */
void Hopper::FireThenRetract(double wait_time = PISTON_DELAY_TIME) {
	ExtendLoadPiston();
	Wait(wait_time);
	RetractLoadPiston();
}

bool Hopper::IsDiscReadyToBePunched() {
	return (LoadBeam->Get() == BROKEN);
}


bool Hopper::IsDiscReadyToBeRolledIn() {
	return (CheckerBeam->Get() == SOLID);
}


bool Hopper::IsHopperFull() {
	return (IsDiscReadyToBePunched() && IsDiscReadyToBeRolledIn());
}



void Hopper::InitDefaultCommand(){}
