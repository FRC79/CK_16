#include "Drivetrain.h"

Drivetrain::Drivetrain() : Subsystem("Drivetrain")
{
	
}

Drivetrain::~Drivetrain()
{
	delete FrontR_Wheel;
	delete FrontL_Wheel;
	delete RearR_Wheel;
	delete RearL_Wheel;
	delete TurnGyro;
	delete RoboDrive;
}

void Drivetrain::InitDefaultCommand()
{
	
}
