#ifndef EXTENDFIREPISTON_H
#define EXTENDFIREPISTON_H

#include "../CommandBase.h"

/* Description */

class ExtendFirePiston : public CommandBase 
{
public:
	ExtendFirePiston();
	ExtendFirePiston(bool runContinuously);
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
