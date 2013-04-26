#include "HopperState.h"

DigitalInput* HopperState::rollerBeam = NULL;
DigitalInput* HopperState::loadBeam = NULL;
DigitalInput* HopperState::fireBeam = NULL;
bool HopperState::autoLoadHalted = false;

void HopperState::init(){
	rollerBeam = RobotMap::rollerBeam;
	loadBeam = RobotMap::loadBeam;
	fireBeam = RobotMap::fireBeam;
}

bool HopperState::IsAutoLoadHalted(){
	return autoLoadHalted;
}

void HopperState::SetAutoLoadHalt(bool isHalted){
	autoLoadHalted = isHalted;
}

bool HopperState::IsDiscUnderneathRollers(){
	return (rollerBeam->Get() == BROKEN);
}

bool HopperState::IsDiscReadyToLoad(){
	return (loadBeam->Get() == BROKEN);
}

bool HopperState::IsDiscInChamber(){
	return (fireBeam->Get() == BROKEN);
}

bool HopperState::IsFull(){
	return (IsDiscUnderneathRollers() && IsDiscReadyToLoad());
}
