#ifndef INVERTWHEELSTATE_H
#define INVERTWHEELSTATE_H

#include "../CommandBase.h"

/* Description */

class InvertWheelState : public CommandBase 
{
public:
	InvertWheelState();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	bool isFinished;
};

#endif
