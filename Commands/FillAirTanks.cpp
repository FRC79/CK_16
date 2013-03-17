#include "FillAirTanks.h"
#include "../RobotMap.h"

FillAirTanks::FillAirTanks()
{
	// Init compressor and pressure switch
	Compressor = new Relay(RobotMap::COMPRESSOR_RELAY_CHANNEL);
	Pressure_SW = new DigitalInput(RobotMap::PRESSURE_SWITCH_CHANNEL);
}

// Called just before this Command runs the first time
void FillAirTanks::Initialize(){}

// Called repeatedly when this Command is scheduled to run
void FillAirTanks::Execute()
{
	// Tells the compressor to keep running until the switch is tripped and the tanks are full.
	Compressor->Set((!Pressure_SW->Get() ? Relay::kForward : Relay::kOff));
}

// Make this return true when this Command no longer needs to run execute()
bool FillAirTanks::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void FillAirTanks::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FillAirTanks::Interrupted()
{
	
}
