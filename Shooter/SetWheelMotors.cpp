#include "SetWheelMotors.h"

SetWheelMotors::SetWheelMotors(float power)
{
	Requires(shooter);
	
	m_power = power;
}

// Called just before this Command runs the first time
void SetWheelMotors::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void SetWheelMotors::Execute()
{
	shooter->SetMotorOutputs(m_power);
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SetWheelMotors::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void SetWheelMotors::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetWheelMotors::Interrupted()
{
	
}
