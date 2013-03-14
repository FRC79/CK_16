#include "Tilt.h"
#include "../RobotMap.h"

Tilt::Tilt() : Subsystem("Tilt")
{
	// Instantiate individual solenoid components
	TiltPiston_In = new Solenoid(RobotMap::TILT_PISTON_IN_ID);
	TiltPiston_Out = new Solenoid(RobotMap::TILT_PISTON_OUT_ID);
	
	// Instantiate corresponding components into DualSolenoids
	TiltPiston = new DualSolenoid(TiltPiston_In, TiltPiston_Out, false, false);
	
	is_tilted_up = false;
}

Tilt::~Tilt()
{
	delete TiltPiston_In;
	delete TiltPiston_Out;
	delete TiltPiston;
}

bool Tilt::IsTiltedUp()
{
	return is_tilted_up;
}

void Tilt::Set(bool tilted_up)
{
	TiltPiston->Set(tilted_up);
	is_tilted_up = tilted_up;
}

void Tilt::InvertCurrentState()
{
	Set(!IsTiltedUp());
}

void Tilt::TiltUp()
{
	Set(true);
}

void Tilt::TiltDown()
{
	Set(false);
}

void Tilt::InitDefaultCommand()
{
	
}
