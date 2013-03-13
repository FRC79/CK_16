#include "Hanger.h"

Hanger::Hanger() : Subsystem("Hanger")
{
	
}

Hanger::~Hanger()
{
	delete HangPiston_A;
	delete HangPiston_B;
}

void Hanger::InitDefaultCommand()
{
	
}
