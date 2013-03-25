#include "FindGoal.h"
#include "SmartDashboard/SmartDashboard.h"
#include "../RobotMap.h"
#include "../RobotState.h"

FindGoal::FindGoal(){}

// Called just before this Command runs the first time
void FindGoal::Initialize()
{
	// Init States and Variables
	is_finished = false;
	found = false;
	azimuth = 0.0;
	range = 0.0;
	RobotState::target_found = false;
	RobotState::azimuth = 0.0;
	RobotState::range = 0.0;
}

// Called repeatedly when this Command is scheduled to run
void FindGoal::Execute()
{
	// Query SmartDashboard for target found status
	found = SmartDashboard::GetBoolean(RobotMap::FOUND_KEY);
	
	// If we found one, query for the azimuth and range data
	if(found)
	{
		azimuth = SmartDashboard::GetNumber(RobotMap::AZIMUTH_KEY);
		range = SmartDashboard::GetNumber(RobotMap::RANGE_KEY);
		
		// Finish the task
		is_finished = true;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool FindGoal::IsFinished()
{
	return is_finished;
}

// Called once after isFinished returns true
void FindGoal::End()
{
	// Update Target Tracking State Variables
	RobotState::target_found = found;
	RobotState::azimuth = azimuth;
	RobotState::range = range;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void FindGoal::Interrupted(){}
