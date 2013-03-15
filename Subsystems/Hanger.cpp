#include "Hanger.h"
#include "../RobotMap.h"

Hanger::Hanger() : Subsystem("Hanger")
{
	// Instantiate the matching solenoid components as DoubleSolenoids
	HangPiston_A = new DoubleSolenoid(RobotMap::HANG_PISTON_A_IN_ID, 
			RobotMap::HANG_PISTON_A_OUT_ID);
	HangPiston_B = new DoubleSolenoid(RobotMap::HANG_PISTON_B_IN_ID,
			RobotMap::HANG_PISTON_B_OUT_ID);
	
	is_extended = false;
}

Hanger::~Hanger()
{
	delete HangPiston_A;
	delete HangPiston_B;
}

bool Hanger::IsHangerExtended()
{
	return is_extended;
}

void Hanger::Set(bool extend_state)
{
	HangPiston_A->Set(extend_state ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
	HangPiston_B->Set(!extend_state ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
	// PROBABLY NEED TO ADD A DELAY IN HERE SINCE
	// IT TAKES SOME TIME TO CHANGE POSTION.
	is_extended = extend_state;
}

void Hanger::InverseCurrentState()
{
	Set(!IsHangerExtended());
}

void Hanger::Extend()
{
	Set(true);
}

void Hanger::Retract()
{
	Set(false);
}

void Hanger::InitDefaultCommand()
{
	
}
