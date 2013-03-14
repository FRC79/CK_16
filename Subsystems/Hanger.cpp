#include "Hanger.h"
#include "../RobotMap.h"

Hanger::Hanger() : Subsystem("Hanger")
{
	// Instantiate the individual solenoid components
	HangPiston_A_In = new Solenoid(RobotMap::HANG_PISTON_A_IN_ID);
	HangPiston_A_Out = new Solenoid(RobotMap::HANG_PISTON_A_OUT_ID);
	HangPiston_B_In = new Solenoid(RobotMap::HANG_PISTON_B_IN_ID);
	HangPiston_B_Out = new Solenoid(RobotMap::HANG_PISTON_B_OUT_ID);
	
	// Instantiate the matching solenoid components as DualSolenoids
	HangPiston_A = new DualSolenoid(HangPiston_A_In, HangPiston_A_Out, false, false);
	HangPiston_B = new DualSolenoid(HangPiston_B_In, HangPiston_B_Out, false, false);
	
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
	HangPiston_A->Set(extend_state);
	HangPiston_B->Set(!extend_state);
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
