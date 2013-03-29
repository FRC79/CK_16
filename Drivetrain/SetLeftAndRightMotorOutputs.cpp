#include "SetLeftAndRightMotorOutputs.h"

SetLeftAndRightMotorOutputs::SetLeftAndRightMotorOutputs(float left_power, float right_power)
{
	Requires(drive);
	
	m_left_power = left_power;
	m_right_power = right_power;
}

// Called just before this Command runs the first time
void SetLeftAndRightMotorOutputs::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void SetLeftAndRightMotorOutputs::Execute()
{
	drive->SetLeftAndRightMotorOutputs(m_left_power, m_right_power);
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SetLeftAndRightMotorOutputs::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void SetLeftAndRightMotorOutputs::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetLeftAndRightMotorOutputs::Interrupted()
{
	
}
