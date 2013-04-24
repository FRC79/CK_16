#ifndef INVERTTILTSTATE_H
#define INVERTTILTSTATE_H

#include "../CommandBase.h"

/* Description */

class InvertTiltState : public CommandBase 
{
public:
	InvertTiltState();
	InvertTiltState(bool runContinuously);
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
