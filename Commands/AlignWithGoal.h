#ifndef ALIGNWITHGOAL_H
#define ALIGNWITHGOAL_H

#include "../CommandBase.h"

/*
 * This command is used to talk to the camera, interface
 * with the gyro, and get the robot to turn the appropriate
 * amount to line up with the goal we are tracking.
 */

class AlignWithGoal : public CommandBase 
{
public:
	AlignWithGoal();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
