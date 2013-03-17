#include "Hopper.h"
#include "../RobotMap.h"
#include "Timer.h"

// Constructor: where we construct things (initialization)
Hopper::Hopper() : Subsystem("Hopper")
{
	Roller = new CANJaguar(RobotMap::ROLLER_MOTOR_ID);
	LoadPiston = new Solenoid(RobotMap::HOPPER_LOAD_PISTON_ID);
	LoadBeam = new DigitalInput(RobotMap::LOAD_BEAM_SENSOR_ID);
	RollerBeam = new DigitalInput(RobotMap::ROLLER_BEAM_SENSOR_ID);
	
	is_extended = false; // Prevent explosions
}

Hopper::~Hopper()
{
	delete Roller;
	delete LoadPiston;
	delete LoadBeam;
	delete RollerBeam;
}

void Hopper::SetRollerMotor(float power){
	Roller->Set(power);
}

void Hopper::StopRollerMotor(){
	Roller->Set(0.0);
}

bool Hopper::IsLoadPistonExtended() {
	return is_extended;
}

void Hopper::SetLoadPiston(bool piston_state) {
	LoadPiston->Set(piston_state);
	is_extended = piston_state;
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
void Hopper::FireThenRetractLoadPiston(double wait_time = PISTON_DELAY_TIME) {
	ExtendLoadPiston();
	Wait(wait_time);
	RetractLoadPiston();
}

bool Hopper::IsDiscReadyToBePunchedDown() {
	return (LoadBeam->Get() == BROKEN);
}


bool Hopper::IsDiscUnderneathRollers() {
	return (RollerBeam->Get() == BROKEN);
}


bool Hopper::IsFull() {
	return (IsDiscReadyToBePunchedDown() && IsDiscUnderneathRollers());
}



void Hopper::InitDefaultCommand(){}
