#ifndef ROLLDISCIN_H
#define ROLLDISCIN_H

#include "../CommandBase.h"

/* Description */

class RollDiscIn : public CommandBase 
{
public:
	RollDiscIn();
	RollDiscIn(bool runContinuously);
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
