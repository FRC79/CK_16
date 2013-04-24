#ifndef RETRACTLOADPISTON_H
#define RETRACTLOADPISTON_H

#include "Commands/Command.h"

/* Description */

class RetractLoadPiston : public Command 
{
public:
	RetractLoadPiston();
	RetractLoadPiston(bool runContinuously);
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
