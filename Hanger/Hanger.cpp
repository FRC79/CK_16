#include "Hanger.h"

Hanger::Hanger() : Subsystem("Hanger")
{
	// Init components
	isExtended = false;
	hangA = RobotMap::hangPistonA;
	hangB = RobotMap::hangPistonB;
}

void Hanger::Set(bool state){
	hangA->Set(state ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
	hangB->Set(!state ? DoubleSolenoid::kForward : DoubleSolenoid::kReverse);
	isExtended = state;
}

bool Hanger::IsExtended(){
	return isExtended;
}

void Hanger::Extend(){
	Set(true);	
}

void Hanger::Retract(){
	Set(false);
}

void Hanger::InvertCurrentState(){
	Set(!IsExtended());
}

/* We don't want it to retract on its own because we're going to
 * be inverting it most of the time. */
void Hanger::InitDefaultCommand()
{
}
