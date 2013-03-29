#include "SetMotorOutputs.h"

SetMotorOutputs::SetMotorOutputs(float power)
{
	Requires(drive);
	
	m_power = power;
}

// Called just before this Command runs the first time
void SetMotorOutputs::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void SetMotorOutputs::Execute()
{
	drive->SetMotorOutputs(m_power);
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SetMotorOutputs::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void SetMotorOutputs::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetMotorOutputs::Interrupted()
{
	
}
