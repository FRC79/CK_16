#ifndef ALIGNWITHGOAL_H
#define ALIGNWITHGOAL_H

#include "Commands/CommandGroup.h"

#include "FindGoal.h"
#include "PointTurn.h"

/*
 * This command is used to talk to the camera, interface
 * with the gyro, and get the robot to turn the appropriate
 * amount to line up with the goal we are tracking.
 */

class AlignWithGoal : public CommandGroup 
{
public:
	AlignWithGoal();
};

#endif
