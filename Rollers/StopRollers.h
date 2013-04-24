#ifndef STOPROLLERS_H
#define STOPROLLERS_H

#include "../CommandBase.h"

/* Description */

class StopRollers : public CommandBase 
{
public:
	StopRollers();
	StopRollers(bool runContinuously);
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
