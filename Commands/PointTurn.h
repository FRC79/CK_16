#ifndef POINTTURN_H
#define POINTTURN_H

#include "../CommandBase.h"

/* This command handles turning the robot's base around
 * its center of rotation using feedback from gyro
 * to tell how much the robot has turned. */

class PointTurn : public CommandBase 
{
public:
	
	typedef enum {kClockwise = 1, kCounterClockwise = -1} TurnDirection;
	
	PointTurn(); // Only use this constructor if you are using Camera for alignment.
	PointTurn(float angle, TurnDirection direction);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	
private:
	void RegularInit();
	void GoalAlignmentInit();
	
	bool special_init;
	float directionCoeff;
	float finalAngle;
	float motorOut;
	bool finished_turning;
};

#endif
