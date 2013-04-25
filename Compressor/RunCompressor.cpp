#include "RunCompressor.h"

RunCompressor::RunCompressor()
{
	// Init components
	this->compressor = RobotMap::compressor;
	this->pressureSwitch = RobotMap::pressureSwitch;
}

// Called just before this Command runs the first time
void RunCompressor::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void RunCompressor::Execute()
{
	// Runs the compressor until switch is tripped and we have enough air
	compressor->Set((!pressureSwitch->Get() ? Relay::kForward : Relay::kOff));
}

// Make this return true when this Command no longer needs to run execute()
bool RunCompressor::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void RunCompressor::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunCompressor::Interrupted()
{
	
}
