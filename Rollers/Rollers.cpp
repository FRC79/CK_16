#include "Rollers.h"
#include "StopRollers.h"

Rollers::Rollers() : Subsystem("Rollers")
{
	roller = RobotMap::rollerMotor;
}

void Rollers::Set(float power){
	roller->Set(power);
}

void Rollers::Stop(){
	Set(0.0);
}

void Rollers::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new StopRollers(true));
}
