#ifndef ROLLDISCOUT_H
#define ROLLDISCOUT_H

#include "../CommandBase.h"
#include "../RobotMap.h"

/* Description */

class RollDiscOut : public CommandBase 
{
public:
	RollDiscOut();
	RollDiscOut(bool runContinuously);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
	bool runsForever;
};

#endif
