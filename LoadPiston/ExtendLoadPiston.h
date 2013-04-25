#ifndef EXTENDLOADPISTON_H
#define EXTENDLOADPISTON_H

#include "../CommandBase.h"

/* Description */

class ExtendLoadPiston : public CommandBase 
{
public:
	ExtendLoadPiston();
	ExtendLoadPiston(bool runContinuously);
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
