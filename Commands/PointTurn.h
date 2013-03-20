#ifndef POINTTURN_H
#define POINTTURN_H

#include "../CommandBase.h"

/* This command handles turning the robot's base around
 * its center of rotation using feedback from encoders
 * to tell how much the robot has turned. */

class PointTurn : public CommandBase 
{
public:
	
	typedef enum {kClockwise = 1, kCounterClockwise = -1} TurnDirection;
	
	PointTurn(float angle, TurnDirection direction);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	float directionCoeff;
	double distInInches;
	double revs;
	double tics;
	float motorOut;
	bool finished_turning;
};

#endif
