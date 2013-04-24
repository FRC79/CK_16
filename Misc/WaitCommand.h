#ifndef WAITCOMMAND_H
#define WAITCOMMAND_H

#include "Commands/Command.h"
#include "Commands/Subsystem.h"

/* Description */

class WaitC : public Command 
{
public:
	WaitC(double timeInSeconds);
	WaitC(double timeInSeconds, Subsystem *s);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
};

#endif
