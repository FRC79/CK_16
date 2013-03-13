#include "DiscShooter.h"

DiscShooter::DiscShooter() : Subsystem("DiscShooter")
{
	
}

DiscShooter::~DiscShooter()
{
	delete FrontWheel;
	delete BackWheel;
	delete FirePiston;
}

void DiscShooter::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}
