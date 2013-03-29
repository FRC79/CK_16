#include "SetFrontAndBackWheelMotors.h"

SetFrontAndBackWheelMotors::SetFrontAndBackWheelMotors(float front_power, float back_power)
{
	Requires(shooter);
	
	m_front_power = front_power;
	m_back_power = back_power;
}

// Called just before this Command runs the first time
void SetFrontAndBackWheelMotors::Initialize()
{
	is_finished = false;
}

// Called repeatedly when this Command is scheduled to run
void SetFrontAndBackWheelMotors::Execute()
{
	shooter->SetFrontAndBackMotorOutputs(m_front_power, m_back_power);
	is_finished = true;
}

// Make this return true when this Command no longer needs to run execute()
bool SetFrontAndBackWheelMotors::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void SetFrontAndBackWheelMotors::End()
{
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SetFrontAndBackWheelMotors::Interrupted()
{
	
}
