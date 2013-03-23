#ifndef DRIVEDISTANCE_H
#define DRIVEDISTANCE_H

#include "../CommandBase.h"

/* This command handles driving the robot a certain
 * distance using encoders to tell exactly how far
 * the robot has driven. */

class DriveDistance : public CommandBase 
{
public:
	
	typedef enum {kForward = 1, kReverse = -1} Direction;
	
	DriveDistance(double distance_in_inches, Direction direction);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	float directionCoeff;
	double revs_to_distance;
	double prev_rev_compensation;
	float motorOut;
	bool finished_driving;
};

#endif
