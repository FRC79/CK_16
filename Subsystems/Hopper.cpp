#include "Hopper.h"
#include "../RobotMap.h"

// Constructor: where we construct things (initialization)
Hopper::Hopper() : Subsystem("Hopper")
{
	Roller = new CANJaguar(RobotMap::ROLLER_MOTOR_ID);
	LoadPiston = new Solenoid(RobotMap::HOPPER_LOAD_PISTON_ID);
	LoadBeam = new DigitalInput(RobotMap::LOAD_BEAM_SENSOR_ID);
	CheckerBeam = new DigitalInput(RobotMap::CHECKER_BEAM_SENSOR_ID);
}

Hopper::~Hopper()
{
	delete Roller;
	delete LoadPiston;
	delete LoadBeam;
	delete CheckerBeam;
}

void Hopper::InitDefaultCommand(){}
