#include "Tilt.h"
#include "../RobotMap.h"

Tilt::Tilt() : Subsystem("Tilt")
{
	// Instantiate corresponding components into DualSolenoids
	TiltPiston = new DoubleSolenoid(RobotMap::TILT_PISTON_IN_ID, 
			RobotMap::TILT_PISTON_OUT_ID);
	
	is_tilted_up = false;
}

Tilt::~Tilt()
{
	delete TiltPiston;
}

bool Tilt::IsTiltedUp()
{
	return is_tilted_up;
}

void Tilt::Set(bool tilted_up)
{
	TiltPiston->Set(tilted_up ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
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
