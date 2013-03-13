#include "Tilt.h"

Tilt::Tilt() : Subsystem("Tilt")
{
	
}

Tilt::~Tilt()
{
	delete TiltPiston;
}

void Tilt::InitDefaultCommand()
{
	
}
